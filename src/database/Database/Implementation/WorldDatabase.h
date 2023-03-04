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

#ifndef WARHEAD_WORLD_DATABASE_H_
#define WARHEAD_WORLD_DATABASE_H_

#include "DatabaseWorkerPool.h"

enum WorldDatabaseStatements : uint32
{
    /*  Naming standard for defines:
        {DB}_{SEL/INS/UPD/DEL/REP}_{Summary of data changed}
        When updating more than one field, consider looking at the calling function
        name for a suiting suffix.
    */

    WORLD_SEL_CREATURES,
    WORLD_SEL_GAMEOBJECTS,

    MAX_WORLDDATABASE_STATEMENTS
};

class WH_DATABASE_API WorldDatabasePool : public DatabaseWorkerPool
{
public:
    WorldDatabasePool() : DatabaseWorkerPool(DatabaseType::World) { }
    ~WorldDatabasePool() = default;

    //- Loads database type specific prepared statements
    void DoPrepareStatements() override;
};

/// Accessor to the world database
WH_DATABASE_API extern WorldDatabasePool WorldDatabase;

#endif
