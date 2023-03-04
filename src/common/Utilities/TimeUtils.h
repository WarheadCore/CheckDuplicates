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

#ifndef WARHEAD_TIME_UTILS_H_
#define WARHEAD_TIME_UTILS_H_

#include "Define.h"
#include "Duration.h"
#include <string_view>

enum class TimeFormat : uint8
{
    FullText,       // 1 Days 2 Hours 3 Minutes 4 Seconds 5 Milliseconds 6 Microseconds
    ShortText,      // 1d 2h 3m 4s 5ms 6us
    Numeric         // 1:2:3:4:5:6
};

namespace Warhead::Time
{
    WH_COMMON_API Seconds TimeStringTo(std::string_view timestring);
    WH_COMMON_API std::string ToTimeString(Microseconds durationTime, uint8 outCount = 3, TimeFormat timeFormat = TimeFormat::ShortText);

    WH_COMMON_API time_t LocalTimeToUTCTime(time_t time);
    WH_COMMON_API time_t GetLocalHourTimestamp(time_t time, uint8 hour, bool onlyAfterTime = true);
    WH_COMMON_API std::tm TimeBreakdown(time_t t = 0);
    WH_COMMON_API std::string TimeToTimestampStr(Seconds time = 0s, std::string_view fmt = {});
    WH_COMMON_API std::string TimeToHumanReadable(Seconds time = 0s, std::string_view fmt = {});

    WH_COMMON_API time_t GetNextTimeWithDayAndHour(int8 dayOfWeek, int8 hour); // int8 dayOfWeek: 0 (sunday) to 6 (saturday)
    WH_COMMON_API time_t GetNextTimeWithMonthAndHour(int8 month, int8 hour); // int8 month: 0 (january) to 11 (december)

    WH_COMMON_API uint32 GetSeconds(Seconds time = 0s);      // seconds after the minute - [0, 60]
    WH_COMMON_API uint32 GetMinutes(Seconds time = 0s);      // minutes after the hour - [0, 59]
    WH_COMMON_API uint32 GetHours(Seconds time = 0s);        // hours since midnight - [0, 23]
    WH_COMMON_API uint32 GetDayInWeek(Seconds time = 0s);    // days since Sunday - [0, 6]
    WH_COMMON_API uint32 GetDayInMonth(Seconds time = 0s);   // day of the month - [1, 31]
    WH_COMMON_API uint32 GetDayInYear(Seconds time = 0s);    // days since January 1 - [0, 365]
    WH_COMMON_API uint32 GetMonth(Seconds time = 0s);        // months since January - [0, 11]
    WH_COMMON_API uint32 GetYear(Seconds time = 0s);         // years since 1900
}

WH_COMMON_API struct tm* localtime_r(time_t const* time, struct tm* result);

inline TimePoint GetApplicationStartTime()
{
    using namespace std::chrono;
    static const steady_clock::time_point ApplicationStartTime = steady_clock::now();
    return ApplicationStartTime;
}

inline uint32 getMSTime()
{
    using namespace std::chrono;
    return uint32(duration_cast<milliseconds>(steady_clock::now() - GetApplicationStartTime()).count());
}

inline Milliseconds GetTimeMS()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(steady_clock::now() - GetApplicationStartTime());
}

inline uint32 getMSTimeDiff(uint32 oldMSTime, uint32 newMSTime)
{
    // getMSTime() have limited data range and this is case when it overflow in this tick
    if (oldMSTime > newMSTime)
        return (0xFFFFFFFF - oldMSTime) + newMSTime;
    else
        return newMSTime - oldMSTime;
}

inline Milliseconds GetMSTimeDiff(Milliseconds oldMSTime, Milliseconds newMSTime)
{
    if (oldMSTime > newMSTime)
        return oldMSTime - newMSTime;
    else
        return newMSTime - oldMSTime;
}

inline uint32 getMSTimeDiff(uint32 oldMSTime, TimePoint newTime)
{
    using namespace std::chrono;

    uint32 newMSTime = uint32(duration_cast<milliseconds>(newTime - GetApplicationStartTime()).count());
    return getMSTimeDiff(oldMSTime, newMSTime);
}

inline uint32 GetMSTimeDiffToNow(uint32 oldMSTime)
{
    return getMSTimeDiff(oldMSTime, getMSTime());
}

inline Milliseconds GetMSTimeDiffToNow(Milliseconds oldMSTime)
{
    return GetMSTimeDiff(oldMSTime, GetTimeMS());
}

inline Seconds GetEpochTime()
{
    using namespace std::chrono;
    return duration_cast<Seconds>(system_clock::now().time_since_epoch());
}

#endif
