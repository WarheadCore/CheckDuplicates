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

#include "WorldDatabase.h"
#include "DatabaseEnv.h"

WorldDatabasePool WorldDatabase;

void WorldDatabasePool::DoPrepareStatements()
{
    SetStatementSize(MAX_WORLDDATABASE_STATEMENTS);

    PrepareStatement(WORLD_SEL_CREATURES_ALL, "SELECT `guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `position_x`, `position_y`, `position_z`, `orientation` FROM `creature` ORDER BY `guid`", CONNECTION_SYNCH);
    PrepareStatement(WORLD_SEL_CREATURES_WITH_MAP, "SELECT `guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `position_x`, `position_y`, `position_z`, `orientation` FROM `creature` WHERE `map` = ? ORDER BY `guid`", CONNECTION_SYNCH);
    PrepareStatement(WORLD_SEL_CREATURES_NAME, "SELECT ct.`entry`, ct.`name`, ctl.`Name` FROM creature_template AS ct LEFT JOIN creature_template_locale ctl ON ct.`entry` = ctl.`entry` AND ctl.`locale` = 'ruRU' AND ct.`name` != ctl.`Name`", CONNECTION_SYNCH);

    PrepareStatement(WORLD_SEL_GAMEOBJECTS_ALL, "SELECT `guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3` FROM `gameobject` ORDER BY `guid`", CONNECTION_SYNCH);
    PrepareStatement(WORLD_SEL_GAMEOBJECTS_WITH_MAP, "SELECT `guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3` FROM `gameobject` WHERE `map` = ? ORDER BY `guid`", CONNECTION_SYNCH);
    PrepareStatement(WORLD_SEL_GAMEOBJECTS_NAME, "SELECT gt.`entry`, gt.`name`, gtl.`Name` FROM `gameobject_template` AS gt LEFT JOIN gameobject_template_locale gtl ON gt.`entry` = gtl.`entry` AND gtl.`locale` = 'ruRU' AND gt.`name` != gtl.`Name`", CONNECTION_SYNCH);
}
