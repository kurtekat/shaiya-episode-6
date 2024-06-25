#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace shaiya
{
    /*
        Example:
        2024-06-24 22:05:01

        Timestamp:
        1639014721

        time_t:
        1719281101
    */
    using Timestamp = unsigned long;

    struct ServerTime
    {
        using Seconds = int;

        // A Unix-like timestamp based on local time. See encoder and decoder.
        Timestamp timestamp;

        static Timestamp add(Timestamp augend, Seconds addend);
        static Timestamp sub(Timestamp minuend, Seconds subtrahend);
        static Timestamp from_time_t(time_t tt);
        static time_t to_time_t(Timestamp timestamp);
        static Timestamp now();
        static void decoder(Timestamp timestamp, LPSYSTEMTIME lt);
        static Timestamp encoder(LPSYSTEMTIME lt);
    };
}
