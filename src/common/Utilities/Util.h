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

#ifndef _UTIL_H
#define _UTIL_H

#include "Define.h"
#include <string>
#include <string_view>
#include <vector>

// UTF8 handling
WH_COMMON_API bool Utf8toWStr(std::string_view utf8str, std::wstring& wstr);
WH_COMMON_API bool Utf8toWStr(char const* utf8str, size_t csize, wchar_t* wstr, size_t& wsize);

inline bool Utf8toWStr(std::string_view utf8str, wchar_t* wstr, size_t& wsize)
{
    return Utf8toWStr(utf8str.data(), utf8str.size(), wstr, wsize);
}

WH_COMMON_API bool WStrToUtf8(std::wstring_view wstr, std::string& utf8str);
WH_COMMON_API bool WStrToUtf8(wchar_t const* wstr, size_t size, std::string& utf8str);

WH_COMMON_API bool StringEqualI(std::string_view str1, std::string_view str2);

#endif
