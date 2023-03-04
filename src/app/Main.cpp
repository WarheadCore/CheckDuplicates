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

#include "Banner.h"
#include "Config.h"
#include "Errors.h"
#include "DatabaseEnv.h"
#include "DatabaseMgr.h"
#include "Log.h"
#include <csignal>
#include <filesystem>

namespace fs = std::filesystem;

/// Launch the server
int main()
{
    signal(SIGABRT, &Warhead::AbortHandler);

    auto configFile = fs::path(sConfigMgr->GetConfigPath() + "WarheadCheckDuplicates.conf");

    // Add file and args in config
    sConfigMgr->Configure(configFile.generic_string());
    if (!sConfigMgr->LoadAppConfigs())
        return 1;

    // Init logging system
    sLog->Initialize();

    Warhead::Banner::Show("checker",
        [](std::string_view text)
        {
            LOG_INFO("checker", "{}", text);
        },
        []()
        {
            LOG_INFO("checker", "> Using configuration file:       {}", sConfigMgr->GetFilename());
            LOG_INFO("checker", "> Using logs directory:           {}", sLog->GetLogsDir());
            LOG_INFO("checker", "> Using DB client version:        {}", sDatabaseMgr->GetClientInfo());
            LOG_INFO("checker", "> Using DB server version:        {}", sDatabaseMgr->GetServerVersion());
        });

    LOG_INFO("checker", "Halting process...");

    // 0 - normal shutdown
    // 1 - shutdown at error
    return 0;
}
