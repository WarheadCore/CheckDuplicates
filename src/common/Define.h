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

#ifndef WARHEAD_DEFINE_H
#define WARHEAD_DEFINE_H

#include "CompilerDefs.h"
#include <cinttypes>
#include <climits>
#include <cstddef>

#if WARHEAD_PLATFORM == WARHEAD_PLATFORM_WINDOWS
#  define _USE_MATH_DEFINES
#endif //WARHEAD_PLATFORM

#ifdef WARHEAD_API_USE_DYNAMIC_LINKING
#  if WARHEAD_COMPILER == WARHEAD_COMPILER_MICROSOFT
#    define WH_API_EXPORT __declspec(dllexport)
#    define WH_API_IMPORT __declspec(dllimport)
#  elif WARHEAD_COMPILER == WARHEAD_COMPILER_GNU
#    define WH_API_EXPORT __attribute__((visibility("default")))
#    define WH_API_IMPORT
#  else
#    error compiler not supported!
#  endif
#else
#  define WH_API_EXPORT
#  define WH_API_IMPORT
#endif

#ifdef WARHEAD_API_EXPORT_COMMON
#  define WH_COMMON_API WH_API_EXPORT
#else
#  define WH_COMMON_API WH_API_IMPORT
#endif

#ifdef WARHEAD_API_EXPORT_DATABASE
#  define WH_DATABASE_API WH_API_EXPORT
#else
#  define WH_DATABASE_API WH_API_IMPORT
#endif

#ifdef WARHEAD_API_EXPORT_CHECKER
#  define WH_CHECK_API WH_API_EXPORT
#else
#  define WH_CHECK_API WH_API_IMPORT
#endif

typedef std::int64_t int64;
typedef std::int32_t int32;
typedef std::int16_t int16;
typedef std::int8_t int8;
typedef std::uint64_t uint64;
typedef std::uint32_t uint32;
typedef std::uint16_t uint16;
typedef std::uint8_t uint8;

#endif // WARHEAD_DEFINE_H
