#
# This file is part of the WarheadCore Project. See AUTHORS file for Copyright information
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#

option(BUILD_TESTING       "Build unit tests"                                            1)
option(WITH_WARNINGS       "Show all warnings during compile"                            0)
option(WITH_DYNAMIC_LINKING "Enable dynamic library linking."                            0)

if(WITH_DYNAMIC_LINKING)
  set(BUILD_SHARED_LIBS ON)
else()
  set(BUILD_SHARED_LIBS OFF)
endif()

# Source tree in IDE
set(WITH_SOURCE_TREE       "hierarchical" CACHE STRING "Build the source tree for IDE's.")
set_property(CACHE WITH_SOURCE_TREE PROPERTY STRINGS no flat hierarchical)

# Config abort
option(CONFIG_ABORT_INCORRECT_OPTIONS "Enable abort if core found incorrect option in config files" 0)
