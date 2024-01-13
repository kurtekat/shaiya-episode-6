#pragma once
#include <chrono>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/shaiya/common.h>

namespace shaiya
{
    struct CGameData;

    class Duration
    {
    public:

        int days;
        int hours;
        int minutes;

        Duration(const SYSTEMTIME& st)
            : days(0), hours(0), minutes(0)
        {
            auto tt = to_time_t(st);
            if (tt == -1)
                return;

            auto tp = std::chrono::system_clock::from_time_t(tt);
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

    private:

        std::time_t to_time_t(const SYSTEMTIME& st)
        {
            std::tm tm{};
            tm.tm_sec = st.wSecond;
            tm.tm_min = st.wMinute;
            tm.tm_hour = st.wHour;
            tm.tm_mday = st.wDay;
            tm.tm_mon = st.wMonth - 1;
            tm.tm_year = st.wYear - 1900;
            tm.tm_isdst = -1;
            return std::mktime(&tm);
        }
    };

    struct ServerTime
    {
        static ULONG GetExpireTime(ULONG time, int days);
        static ULONG GetSystemTime();
        static bool HasDuration(CGameData::ItemInfo* itemInfo);
        static ULONG ServerTimeToSystemTime(ULONG serverTime/*eax*/, LPSYSTEMTIME systemTime/*ecx*/);
        static ULONG SystemTimeToServerTime(LPSYSTEMTIME systemTime);
    };

    inline std::chrono::system_clock::time_point g_world_thread_update_time_point{};
}
