#pragma once
#include <chrono>
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

        Duration(LPSYSTEMTIME lpst)
            : days(0), hours(0), minutes(0)
        {
            auto tt = this->to_time_t(lpst);
            if (tt == -1)
                return;

            auto tp = std::chrono::system_clock::from_time_t(tt);
            auto duration = tp - std::chrono::system_clock::now();

            this->days = std::chrono::duration_cast<std::chrono::days>(duration).count();
            this->hours = std::chrono::duration_cast<std::chrono::hours>(duration).count();
            this->minutes = std::chrono::duration_cast<std::chrono::minutes>(duration).count();
        }

        bool expired()
        {
            return days <= 0 && hours <= 0 && minutes <= 0;
        }

    private:

        std::time_t to_time_t(LPSYSTEMTIME lpst)
        {
            std::tm tm{};
            tm.tm_sec = lpst->wSecond;
            tm.tm_min = lpst->wMinute;
            tm.tm_hour = lpst->wHour;
            tm.tm_mday = lpst->wDay;
            tm.tm_mon = lpst->wMonth - 1;
            tm.tm_year = lpst->wYear - 1900;
            tm.tm_isdst = -1;
            return std::mktime(&tm);
        }
    };

    struct ServerTime
    {
        static ULONG GetExpireTime(ULONG makeTime, int days);
        static ULONG GetSystemTime();
        static bool IsTimedItem(CGameData::ItemInfo* itemInfo);
        static ULONG ServerTimeToSystemTime(ULONG time/*eax*/, LPSYSTEMTIME lpst/*ecx*/);
        static ULONG SystemTimeToServerTime(LPSYSTEMTIME lpst);
    };
}
