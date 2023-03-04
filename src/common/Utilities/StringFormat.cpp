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

// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "StringFormat.h"
#include <locale>

constexpr char CHAR_WHITESPACE = ' ';

template<class Str>
WH_COMMON_API Str Warhead::String::Trim(const Str& s, const std::locale& loc /*= std::locale()*/)
{
    typename Str::const_iterator first = s.begin();
    typename Str::const_iterator end = s.end();

    while (first != end && std::isspace(*first, loc))
    {
        ++first;
    }

    if (first == end)
    {
        return Str();
    }

    typename Str::const_iterator last = end;

    do
    {
        --last;
    } while (std::isspace(*last, loc));

    if (first != s.begin() || last + 1 != end)
    {
        return Str(first, last + 1);
    }

    return s;
}

std::string_view Warhead::String::TrimLeft(std::string_view str)
{
    while (!str.empty() && (str.front() == CHAR_WHITESPACE))
        str.remove_prefix(1);

    return str;
}

std::string_view Warhead::String::TrimRight(std::string_view str)
{
    while (!str.empty() && (str.back() == CHAR_WHITESPACE))
        str.remove_suffix(1);

    return str;
}

// Template Trim
template WH_COMMON_API std::string Warhead::String::Trim<std::string>(const std::string& s, const std::locale& loc /*= std::locale()*/);
