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

#ifndef _WARHEAD_FILE_UTIL_H_
#define _WARHEAD_FILE_UTIL_H_

#include "Define.h"
#include <string_view>

namespace Warhead::File
{
    WH_COMMON_API void CorrectDirPath(std::string& path, bool makeAbsolute = false);
    WH_COMMON_API bool CreateDirIfNeed(std::string_view path);
    WH_COMMON_API std::size_t FindWord(std::string_view path, std::string_view findWord);
    WH_COMMON_API bool CopyFile(std::string_view pathFrom, std::string_view pathTo);
}

#endif // _WARHEAD_FILE_UTIL_H_
