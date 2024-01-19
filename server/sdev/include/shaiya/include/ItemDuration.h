#pragma once
#include <chrono>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/shaiya/common.h>
#include <include/shaiya/include/CGameData.h>

namespace shaiya
{
    class ItemDuration
    {
    public:

        int days;
        int hours;
        int minutes;

        ItemDuration(const SYSTEMTIME& st)
            : days(0), hours(0), minutes(0)
        {
            std::tm tm{};
            tm.tm_sec = st.wSecond;
            tm.tm_min = st.wMinute;
            tm.tm_hour = st.wHour;
            tm.tm_mday = st.wDay;
            tm.tm_mon = st.wMonth - 1;
            tm.tm_year = st.wYear - 1900;
            tm.tm_isdst = -1;

            auto time = std::mktime(&tm);
            if (time == -1)
                return;

            auto tp = std::chrono::system_clock::from_time_t(time);
            auto duration = tp - std::chrono::system_clock::now();

            days = std::chrono::duration_cast<std::chrono::days>(duration).count();
            hours = std::chrono::duration_cast<std::chrono::hours>(duration).count();
            minutes = std::chrono::duration_cast<std::chrono::minutes>(duration).count();

            days = (days < 0) ? 0 : days;
            hours = (hours < 0) ? 0 : hours;
            minutes = (minutes < 0) ? 0 : minutes;
        }

        constexpr bool expired() const
        {
            return !days && !hours && !minutes;
        }
    };

    bool ItemHasDuration(CGameData::ItemInfo* itemInfo);
}
