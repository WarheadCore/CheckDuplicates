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

#ifndef WARHEAD_WORLD_OBJECT_H_
#define WARHEAD_WORLD_OBJECT_H_

#include "Define.h"
#include <list>
#include <string>
#include <string_view>
#include <unordered_map>

template<typename ObjectType>
class WH_CHECK_API WorldObject
{
public:
    void StartCheck(uint32 mapID, std::string_view dir);

    inline std::size_t GetDuplicatesCount() { return _duplicatesCount; }

private:
    void LoadObjectsFromDB();
    void LoadObjectNames();
    void CheckDuplicates();
    void OutResults();

    std::pair<std::string, std::string> const* GetObjectNames(uint32 id);

    std::unordered_map<uint64/*guid*/, ObjectType> _objects;
    std::unordered_map<uint64/*guid*/, std::list<ObjectType const*>> _duplicateObjects;
    std::unordered_map<uint32 /*ID*/, std::pair<std::string, std::string>> _objectNames;
    std::size_t _duplicatesCount{};
    uint32 _mapID{};
    std::string _outDir;
};

#endif
