#pragma once
#include <chrono>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace shaiya
{
    /*
        A Unix-like timestamp based on local time.

        Example:
        2024-06-24 22:05:01

        Timestamp:
        1639014721

        time_t:
        1719281101
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

        ServerTime(const SYSTEMTIME& lt)
            : timestamp(0)
        {
            timestamp = from_SYSTEMTIME(lt);
        }

        std::chrono::year year() const;
        std::chrono::month month() const;
        std::chrono::day day() const;
        std::chrono::hours hours() const;
        std::chrono::minutes minutes() const;
        std::chrono::seconds seconds() const;

        Timestamp add(std::chrono::seconds ss) const;
        Timestamp sub(std::chrono::seconds ss) const;

        static Timestamp from_SYSTEMTIME(const SYSTEMTIME& lt);
        static void to_SYSTEMTIME(Timestamp ts, SYSTEMTIME& lt);
        static Timestamp from_time_t(time_t tt);
        static time_t to_time_t(Timestamp ts);
        static void to_tm(Timestamp ts, std::tm& tm);
        static Timestamp now();
    };
}
