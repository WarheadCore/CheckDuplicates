#
# This file is part of the WarheadCore Project. See AUTHORS file for Copyright information
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU Affero General Public License as published by the
# Free Software Foundation; either version 3 of the License, or (at your
# option) any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
# more details.
#
# You should have received a copy of the GNU General Public License along
# with this program. If not, see <http://www.gnu.org/licenses/>.
#

# output generic information about the core and buildtype chosen
message(STATUS "")

if (UNIX)
  message(STATUS "* Buildtype                       : ${CMAKE_BUILD_TYPE}")
endif()

message(STATUS "*")

# output information about installation-directories and locations
message(STATUS "* Install server to               : ${CMAKE_INSTALL_PREFIX}")
if (UNIX)
  message(STATUS "* Install libraries to            : ${LIBSDIR}")
endif()

message(STATUS "* Install configs to              : ${CONF_DIR}")
add_definitions(-D_CONF_DIR=$<1:"${CONF_DIR}">)

message(STATUS "*")

if (BUILD_TESTING)
  message(STATUS "* Build unit tests                : Yes")
else()
  message(STATUS "* Build unit tests                : No (default)")
endif()

if (WITH_WARNINGS)
  message(STATUS "* Show all warnings               : Yes")
else()
  message(STATUS "* Show compile-warnings           : No (default)")
endif()

if (WIN32)
  if (NOT WITH_SOURCE_TREE STREQUAL "no")
    message(STATUS "* Show source tree                : Yes - \"${WITH_SOURCE_TREE}\"")
  else()
    message(STATUS "* Show source tree                : No")
  endif()
else()
  message(STATUS "* Show source tree                : No (For UNIX default)")
endif()

if (BUILD_SHARED_LIBS)
  message(STATUS "")
  message(STATUS " *** WITH_DYNAMIC_LINKING - INFO!")
  message(STATUS " *** Will link against shared libraries!")

  add_definitions(-DWARHEAD_API_USE_DYNAMIC_LINKING)
endif()

if (CONFIG_ABORT_INCORRECT_OPTIONS)
  message(STATUS "")
  message(STATUS " WARNING !")
  message(STATUS " Enabled abort if core found incorrect option in config files")

  add_definitions(-DCONFIG_ABORT_INCORRECT_OPTIONS)
endif()

message(STATUS "")
