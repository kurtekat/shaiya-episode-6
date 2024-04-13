#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/shaiya/common.h>

namespace shaiya
{
    struct ServerTime
    {
        static ULONG Add(ULONG base, long long seconds);
        static ULONG GetSystemTime();
        static void ServerTimeToSystemTime(ULONG serverTime/*eax*/, LPSYSTEMTIME systemTime/*ecx*/);
        static ULONG SystemTimeToServerTime(LPSYSTEMTIME systemTime);
    };
}
