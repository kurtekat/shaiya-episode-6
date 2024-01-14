#include <chrono>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/shaiya/include/ServerTime.h>
using namespace shaiya;

ULONG ServerTime::Add(ULONG base, long long seconds)
{
    using namespace std::chrono_literals;

    SYSTEMTIME st{};
    ServerTime::ServerTimeToSystemTime(base, &st);

    FILETIME ft{};
    if (!SystemTimeToFileTime(&st, &ft))
        return 0;

    ULARGE_INTEGER li{ ft.dwLowDateTime, ft.dwHighDateTime };
    li.QuadPart += seconds * std::chrono::microseconds(10s).count();

    ft.dwLowDateTime = li.LowPart;
    ft.dwHighDateTime = li.HighPart;

    if (!FileTimeToSystemTime(&ft, &st))
        return 0;

    return ServerTime::SystemTimeToServerTime(&st);
}

ULONG ServerTime::GetSystemTime()
{
    typedef ULONG(__stdcall* LPFN)();
    return (*(LPFN)0x4E1A50)();
}

void ServerTime::ServerTimeToSystemTime(ULONG serverTime/*eax*/, LPSYSTEMTIME systemTime/*ecx*/)
{
    Address u0x4E1CA0 = 0x4E1CA0;

    __asm
    {
        mov eax,serverTime
        mov ecx,systemTime
        call u0x4E1CA0
    }
}

ULONG ServerTime::SystemTimeToServerTime(LPSYSTEMTIME systemTime/*ecx*/)
{
    Address u0x4E1CF0 = 0x4E1CF0;

    __asm
    {
        mov ecx,systemTime
        call u0x4E1CF0
    }
}
