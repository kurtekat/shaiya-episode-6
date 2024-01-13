#include <chrono>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/shaiya/include/CGameData.h>
#include <include/shaiya/include/ServerTime.h>
using namespace shaiya;

ULONG ServerTime::GetExpireTime(ULONG time, int days)
{
    using namespace std::chrono_literals;

    if (days <= 0)
        return 0;

    SYSTEMTIME st{};
    ServerTime::ServerTimeToSystemTime(time, &st);

    FILETIME ft{};
    SystemTimeToFileTime(&st, &ft);

    ULARGE_INTEGER li{ ft.dwLowDateTime, ft.dwHighDateTime };

    auto seconds = std::chrono::seconds(std::chrono::days(days)).count();
    li.QuadPart += seconds * std::chrono::microseconds(10s).count();

    ft.dwLowDateTime = li.LowPart;
    ft.dwHighDateTime = li.HighPart;

    FileTimeToSystemTime(&ft, &st);
    return ServerTime::SystemTimeToServerTime(&st);
}

ULONG ServerTime::GetSystemTime()
{
    typedef ULONG(__stdcall* LPFN)();
    return (*(LPFN)0x4E1A50)();
}

bool ServerTime::HasDuration(CGameData::ItemInfo* itemInfo)
{
    if (!itemInfo)
        return false;

    int days = itemInfo->range;
    if (days <= 0)
        return false;

    switch (static_cast<CGameData::ItemType>(itemInfo->type))
    {
    case CGameData::ItemType::Pet:
    case CGameData::ItemType::Costume:
        return true;
    default:
        break;
    }

    return false;
}

ULONG ServerTime::ServerTimeToSystemTime(ULONG serverTime/*eax*/, LPSYSTEMTIME systemTime/*ecx*/)
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
