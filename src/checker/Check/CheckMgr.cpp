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

#include "CheckMgr.h"
#include "Config.h"
#include "DatabaseEnv.h"
#include "Errors.h"
#include "FileUtil.h"
#include "Log.h"
#include "StopWatch.h"

/*static*/ CheckMgr* CheckMgr::instance()
{
    static CheckMgr instance;
    return &instance;
}

void CheckMgr::StartCheck()
{
    StopWatch sw;

    LoadConfig();
    LoadCreatures();
    LoadGameObjects();

    LOG_INFO("checker", "All checks end. Elapsed: {}", sw);
    LOG_INFO("checker", "");
}

void CheckMgr::LoadConfig()
{
    LOG_INFO("checker", "Load config options");

    _checkCreature = sConfigMgr->GetOption<bool>("Checker.Creature.Enable", false);
    _checkGameObjects = sConfigMgr->GetOption<bool>("Checker.GameObjects.Enable", false);
    _mapID = sConfigMgr->GetOption<uint32>("Checker.MapID", 0);
    _sqlOutDir = sConfigMgr->GetOption<std::string>("SQLOutDir", "sql");

    Warhead::File::CorrectDirPath(_sqlOutDir);
    ASSERT(Warhead::File::CreateDirIfNeed(_sqlOutDir));

    LOG_INFO("checker", "- Enable check creature: {}", _checkCreature);
    LOG_INFO("checker", "- Enable check gameobjects: {}", _checkGameObjects);
    LOG_INFO("checker", "- Check in map: {}", _mapID);
    LOG_INFO("checker", "- SQL dir: {}", _sqlOutDir);
    LOG_INFO("checker", "");
}

void CheckMgr::LoadCreatures()
{
    if (!_checkCreature)
        return;

    _creatures.StartCheck(_mapID, _sqlOutDir);
}

void CheckMgr::LoadGameObjects()
{
    if (!_checkGameObjects)
        return;

    _gameObjects.StartCheck(_mapID, _sqlOutDir);
}
