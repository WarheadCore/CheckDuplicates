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

#include "ObjectDefines.h"
#include "DatabaseEnv.h"

BaseObject::BaseObject(PreparedResultSet const& fields)
{
    uint8 index{};

    Guid = fields[index++].Get<uint64>();
    ID = fields[index++].Get<uint32>();
    ZoneID = fields[index++].Get<uint16>();
    AreaID = fields[index++].Get<uint16>();
    SpawnDifficulties = fields[index++].Get<uint32>();
    PhaseId = fields[index++].Get<uint32>();
    PosX = fields[index++].Get<float>();
    PosY = fields[index++].Get<float>();
    PosZ = fields[index++].Get<float>();
    Orientation = fields[index++].Get<float>();
}

bool BaseObject::IsDuplicateWith(BaseObject const& object) const
{
    if (ID != object.ID)
        return false;

    if (MapID != object.MapID)
        return false;

    if (ZoneID != object.ZoneID)
        return false;

    if (AreaID != object.AreaID)
        return false;

    if (PhaseId != object.PhaseId)
        return false;

    if (SpawnDifficulties != object.SpawnDifficulties)
        return false;

    if (PosX != object.PosX)
        return false;

    if (PosY != object.PosY)
        return false;

    if (PosZ != object.PosZ)
        return false;

    if (Orientation != object.Orientation)
        return false;

    return true;
}

Creature::Creature(PreparedResultSet const& fields) :
    BaseObject(fields) { }

bool Creature::IsDuplicateWith(Creature const& object) const
{
    if (!BaseObject::IsDuplicateWith(object))
        return false;

    return true;
}

GameObject::GameObject(PreparedResultSet const& fields) :
    BaseObject(fields)
{
    uint8 index{ 11 };

    Rotation0 = fields[index++].Get<float>();
    Rotation1 = fields[index++].Get<float>();
    Rotation2 = fields[index++].Get<float>();
    Rotation3 = fields[index++].Get<float>();
}

bool GameObject::IsDuplicateWith(GameObject const& object) const
{
    if (!BaseObject::IsDuplicateWith(object))
        return false;

    if (Rotation0 != object.Rotation0)
        return false;

    if (Rotation1 != object.Rotation1)
        return false;

    if (Rotation2 != object.Rotation2)
        return false;

    if (Rotation3 != object.Rotation3)
        return false;

    return true;
}
