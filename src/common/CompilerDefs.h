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

#ifndef WARHEAD_COMPILERDEFS_H
#define WARHEAD_COMPILERDEFS_H

#define WARHEAD_PLATFORM_WINDOWS 0
#define WARHEAD_PLATFORM_UNIX    1
#define WARHEAD_PLATFORM_APPLE   2

// must be first (win 64 also define _WIN32)
#if defined( _WIN64 )
#define WARHEAD_PLATFORM WARHEAD_PLATFORM_WINDOWS
#elif defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 )
#define WARHEAD_PLATFORM WARHEAD_PLATFORM_WINDOWS
#elif defined( __APPLE_CC__ )
#define WARHEAD_PLATFORM WARHEAD_PLATFORM_APPLE
#else
#define WARHEAD_PLATFORM WARHEAD_PLATFORM_UNIX
#endif

#define WARHEAD_COMPILER_MICROSOFT 0
#define WARHEAD_COMPILER_GNU       1

#ifdef _MSC_VER
#define WARHEAD_COMPILER WARHEAD_COMPILER_MICROSOFT
#elif defined( __GNUC__ )
#define WARHEAD_COMPILER WARHEAD_COMPILER_GNU
#else
#  error "FATAL ERROR: Unknown compiler."
#endif

#endif
