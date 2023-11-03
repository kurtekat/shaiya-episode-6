#pragma once
#include <chrono>
#include <include/shaiya/common.h>

namespace shaiya
{
    class Duration
    {
    public:

        int days;
        int hours;
        int minutes;

        Duration(LPSYSTEMTIME time)
            : days(0), hours(0), minutes(0)
        {
            auto tt = this->to_time_t(time);
            if (tt == -1)
                return;

            auto time_point = std::chrono::system_clock::from_time_t(tt);
            auto duration = time_point - std::chrono::system_clock::now();

            this->days = std::chrono::duration_cast<std::chrono::days>(duration).count();
            this->hours = std::chrono::duration_cast<std::chrono::hours>(duration).count();
            this->minutes = std::chrono::duration_cast<std::chrono::minutes>(duration).count();
        }

        bool expired()
        {
            return days <= 0 && hours <= 0 && minutes <= 0;
        }

    private:

        std::time_t to_time_t(LPSYSTEMTIME st)
        {
            std::tm tm{};
            tm.tm_sec = st->wSecond;
            tm.tm_min = st->wMinute;
            tm.tm_hour = st->wHour;
            tm.tm_mday = st->wDay;
            tm.tm_mon = st->wMonth - 1;
            tm.tm_year = st->wYear - 1900;
            tm.tm_isdst = -1;
            return std::mktime(&tm);
        }
    };

    struct ServerTime
    {
        static ULONG GetExpireTime(ULONG makeTime, int days);
        static ULONG GetSystemTime();
        static ULONG ServerTimeToSystemTime(ULONG time/*eax*/, LPSYSTEMTIME lpst/*ecx*/);
        static ULONG SystemTimeToServerTime(LPSYSTEMTIME lpst);
    };
}
