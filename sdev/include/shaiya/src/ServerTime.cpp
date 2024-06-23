#include <chrono>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "include/shaiya/include/ServerTime.h"
using namespace shaiya;

ULONG ServerTime::Add(ULONG base, uint64_t seconds)
{
    using Clock = std::chrono::system_clock;

    auto tt = ServerTime::ToTimeT(base);
    if (tt == -1)
        return 0;

    auto tp = Clock::from_time_t(tt) + std::chrono::seconds(seconds);
    return ServerTime::FromTimeT(Clock::to_time_t(tp));
}

ULONG ServerTime::FromSystemTime(LPSYSTEMTIME time/*ecx*/)
{
    Address u0x4E1CF0 = 0x4E1CF0;

    __asm
    {
        mov ecx,time
        call u0x4E1CF0
    }
}

ULONG ServerTime::FromTimeT(time_t time)
{
    std::tm tm{};
    if (localtime_s(&tm, &time))
        return 0;

    SYSTEMTIME st{};
    st.wYear = tm.tm_year + 1900;
    st.wMonth = tm.tm_mon + 1;
    st.wDay = tm.tm_mday;
    st.wHour = tm.tm_hour;
    st.wMinute = tm.tm_min;
    st.wSecond = tm.tm_sec;
    return ServerTime::FromSystemTime(&st);
}

ULONG ServerTime::Now()
{
    // ps_game.GetSystemTime
    typedef ULONG(__stdcall* LPFN)();
    return (*(LPFN)0x4E1A50)();
}

void ServerTime::ToSystemTime(ULONG serverTime/*eax*/, LPSYSTEMTIME systemTime/*ecx*/)
{
    Address u0x4E1CA0 = 0x4E1CA0;

    __asm
    {
        mov eax,serverTime
        mov ecx,systemTime
        call u0x4E1CA0
    }
}

time_t ServerTime::ToTimeT(ULONG time)
{
    SYSTEMTIME st{};
    ServerTime::ToSystemTime(time, &st);

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
