#pragma once
#include <chrono>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace shaiya
{
    /*
        A Unix-like timestamp based on local time.

        Example:
        2063-12-31 23:59:59

        Timestamp:
        4282351355

        time_t:
        2966389199
    */
    using Timestamp = unsigned long;

    class ServerTime
    {
    public:

        Timestamp timestamp;

        ServerTime()
            : timestamp(0)
        {
            timestamp = now();
        }

        ServerTime(Timestamp ts)
            : timestamp(ts)
        {
        }

        std::chrono::year year() const;
        std::chrono::month month() const;
        std::chrono::day day() const;
        std::chrono::hours hours() const;
        std::chrono::minutes minutes() const;
        std::chrono::seconds seconds() const;

        static Timestamp add(Timestamp ts, std::chrono::seconds ss);
        static Timestamp sub(Timestamp ts, std::chrono::seconds ss);

        static Timestamp from_SYSTEMTIME(const SYSTEMTIME& lt);
        static void to_SYSTEMTIME(Timestamp ts, SYSTEMTIME& lt);
        static Timestamp from_time_t(time_t tt);
        static time_t to_time_t(Timestamp ts);
        static Timestamp from_tm(const std::tm& tm);
        static void to_tm(Timestamp ts, std::tm& tm);
        static Timestamp now();
    };
}
