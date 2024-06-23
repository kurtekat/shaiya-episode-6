#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    struct ServerTime
    {
        static ULONG Add(ULONG base, uint64_t seconds);
        static ULONG FromSystemTime(LPSYSTEMTIME time);
        static ULONG FromTimeT(time_t time);
        static ULONG Now();
        static void ToSystemTime(ULONG serverTime/*eax*/, LPSYSTEMTIME systemTime/*ecx*/);
        static time_t ToTimeT(ULONG time);
    };
}
