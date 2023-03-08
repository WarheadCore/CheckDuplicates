/*
 * This file is part of the WarheadCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "WorldObject.h"
#include "Containers.h"
#include "ObjectDefines.h"
#include "DatabaseEnv.h"
#include "GitRevision.h"
#include "Log.h"
#include "StopWatch.h"
#include <fstream>

namespace Warhead
{
    template<typename T>
    struct ObjectDefine { };

    template<>
    struct ObjectDefine<Creature>
    {
        static constexpr auto name = "creature";
        static constexpr auto stmtIndexSelObjects = WORLD_SEL_CREATURES_WITH_MAP;
        static constexpr auto stmtIndexSelObjectsNames = WORLD_SEL_CREATURES_NAME;
    };

    template<>
    struct ObjectDefine<GameObject>
    {
        static constexpr auto name = "gameobject";
        static constexpr auto stmtIndexSelObjects = WORLD_SEL_GAMEOBJECTS_WITH_MAP;
        static constexpr auto stmtIndexSelObjectsNames = WORLD_SEL_GAMEOBJECTS_NAME;
    };
}

template<typename ObjectType>
void WorldObject<ObjectType>::StartCheck(uint32 mapID, std::string_view dir)
{
    _mapID = mapID;
    _outDir = dir;

    LoadObjectsFromDB();
    LoadObjectNames();
    CheckDuplicates();
    OutResults();
}

template<typename ObjectType>
void WorldObject<ObjectType>::LoadObjectsFromDB()
{
    StopWatch sw;

    LOG_INFO("checker", "Loading {}s in map: {}", Warhead::ObjectDefine<ObjectType>::name, _mapID);

    auto stmt = WorldDatabase.GetPreparedStatement(Warhead::ObjectDefine<ObjectType>::stmtIndexSelObjects);
    stmt->SetArguments(_mapID);

    auto result = WorldDatabase.Query(stmt);
    if (!result)
    {
        LOG_ERROR("checker", "Not found {}s in map: {}", Warhead::ObjectDefine<ObjectType>::name, _mapID);
        return;
    }

    _objects.reserve(result->GetRowCount());

    for (auto const& fields : *result)
    {
        ObjectType object(fields);
        _objects.emplace(object.Guid, object);
    }

    LOG_INFO("checker", ">> Loaded {} {}s in {}", _objects.size(), Warhead::ObjectDefine<ObjectType>::name, sw);
    LOG_INFO("checker", "");
}

template<typename ObjectType>
void WorldObject<ObjectType>::LoadObjectNames()
{
    StopWatch sw;

    auto result = WorldDatabase.Query(WorldDatabase.GetPreparedStatement(Warhead::ObjectDefine<ObjectType>::stmtIndexSelObjectsNames));
    if (!result)
        return;

    _objectNames.reserve(result->GetRowCount());

    for (auto const& fields : *result)
    {
        auto objectID = fields[0].template Get<uint32>();
        auto objectName = fields[1].template Get<std::string>();
        std::string objectLocalizedName;

        if (!fields[2].IsNull())
            objectLocalizedName = fields[2].template Get<std::string>();

        _objectNames.emplace(objectID, std::pair{ objectName, objectLocalizedName });
    }
}

template<typename ObjectType>
void WorldObject<ObjectType>::CheckDuplicates()
{
    if (_objects.empty())
    {
        LOG_WARN("checker", "Not found objects for check. Skip");
        return;
    }

    std::unordered_map<uint64/*guid*/, std::list<ObjectType const*>> objectIds;

    for (auto const& [guid, object] : _objects)
        objectIds[object.ID].emplace_back(&object);

    LOG_INFO("checker", "Found {} unique ids", objectIds.size());

    std::list<uint64> duplicateObjects;

    for (auto& [goID, objectList] : objectIds)
    {
        for (auto const& objectCheckLeft : objectList)
        {
            for (auto const& objectCheckRight : objectList)
            {
                // Skip check equal object
                if (objectCheckLeft->Guid == objectCheckRight->Guid)
                    continue;

                if (std::find(duplicateObjects.begin(), duplicateObjects.end(), objectCheckLeft->Guid) != duplicateObjects.end())
                    continue;

                if (std::find(duplicateObjects.begin(), duplicateObjects.end(), objectCheckRight->Guid) != duplicateObjects.end())
                    continue;

                if (objectCheckRight->IsDuplicateWith(*objectCheckLeft))
                {
                    LOG_TRACE("checker", "Found duplicate object {} with {}", objectCheckRight->Guid, objectCheckLeft->Guid);
                    duplicateObjects.emplace_back(objectCheckRight->Guid);
                    _duplicateObjects[objectCheckLeft->Guid].emplace_back(objectCheckRight);
                }
            }
        }
    }

    _duplicatesCount = duplicateObjects.size();

    LOG_INFO("checker", "Found {} duplicates", _duplicatesCount);
    LOG_INFO("checker", "");
}

template<typename ObjectType>
void WorldObject<ObjectType>::OutResults()
{
    if (_duplicateObjects.empty())
    {
        LOG_INFO("checker", "Not found duplicates objects");
        return;
    }

    StopWatch sw;

    std::string name = Warhead::ObjectDefine<ObjectType>::name;
    std::string filePath{ std::string(_outDir) + "remove_" + name + "_duplicates.sql" };

    LOG_INFO("checker", "Start make file: {}", filePath);

    std::ofstream file(filePath);
    if (!file.is_open())
    {
        LOG_ERROR("checker", "Can't open file: {}", filePath);
        return;
    }

    // Header
    file << "/*" << std::endl;
    file << " * " << GitRevision::GetFullVersion() << std::endl;
    file << " *" << std::endl;
    file << " * Check type: " << name << std::endl;
    file << " * Map id: " << _mapID << std::endl;
    file << " */" << std::endl;
    file << std::endl;

    for (auto const& [guid, objectList] : _duplicateObjects)
    {
        auto size = objectList.size();

        file << "/*" << std::endl;
        file << " * " << "Found " << size << " duplicates with guid " << guid << std::endl;

        if (auto names = GetObjectNames(objectList.front()->ID))
        {
            auto objectName = names->first;
            auto objectlocalizedName = names->second;

            file << " * " << objectName;

            if (!objectlocalizedName.empty())
                file << " (" << objectlocalizedName << ")";

            file << std::endl;
        }

        file << " */" << std::endl;

        // Start sql query
        file << "DELETE FROM `" << name << "` WHERE `guid` ";

        if (size >= 2)
        {
            file << "IN" << std::endl << "(";

            std::string str;

            for (auto const& object : objectList)
                str.append(Warhead::StringFormat("{}, ", object->Guid));

            // Del last char
            str.pop_back();
            str.pop_back();

            file << str;
            file << ")";
        }
        else
            file << "= " << objectList.front()->Guid;

        file << ";" << std::endl << std::endl;
    }

    file.close();

    LOG_INFO("checker", "End make file: {}. Elapsed: {}", filePath, sw);
    LOG_INFO("checker", "");
}

template<typename ObjectType>
std::pair<std::string, std::string> const* WorldObject<ObjectType>::GetObjectNames(uint32 id)
{
    return Warhead::Containers::MapGetValuePtr(_objectNames, id);
}

template WH_CHECK_API void WorldObject<Creature>::StartCheck(uint32 mapID, std::string_view dir);
template WH_CHECK_API void WorldObject<GameObject>::StartCheck(uint32 mapID, std::string_view dir);

//template WH_CHECK_API void WorldObject<Creature>::LoadObjectsFromDB();
//template WH_CHECK_API void WorldObject<GameObject>::LoadObjectsFromDB();

//template WH_CHECK_API void WorldObject<Creature>::CheckDuplicates();
//template WH_CHECK_API void WorldObject<GameObject>::CheckDuplicates();

//template WH_CHECK_API void WorldObject<Creature>::OutResults();
//template WH_CHECK_API void WorldObject<GameObject>::OutResults();
