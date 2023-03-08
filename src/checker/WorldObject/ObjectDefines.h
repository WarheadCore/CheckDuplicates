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

#ifndef WARHEAD_WORLD_OBJECT_DEFINES_H_
#define WARHEAD_WORLD_OBJECT_DEFINES_H_

#include "Define.h"

class PreparedResultSet;

struct BaseObject
{
    explicit BaseObject(PreparedResultSet const& fields);

    uint64 Guid{};
    uint32 ID{};
    uint16 MapID{};
    uint16 ZoneID{};
    uint16 AreaID{};
    uint32 PhaseId{};
    uint32 SpawnDifficulties{};

    float PosX{};
    float PosY{};
    float PosZ{};
    float Orientation{};

    [[nodiscard]] bool IsDuplicateWith(BaseObject const& object) const;
};

struct WH_CHECK_API Creature : public BaseObject
{
    explicit Creature(PreparedResultSet const& fields);

    [[nodiscard]] bool IsDuplicateWith(Creature const& object) const;
};

struct WH_CHECK_API GameObject : public BaseObject
{
    explicit GameObject(PreparedResultSet const& fields);

    float Rotation0{};
    float Rotation1{};
    float Rotation2{};
    float Rotation3{};

    [[nodiscard]] bool IsDuplicateWith(GameObject const& object) const;
};

#endif
