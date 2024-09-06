#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/SConnection.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CClientToMgr
    {
        SConnection connection;  //0x00
        PAD(24);
        // 0xE8
    };
    #pragma pack(pop)

    static_assert(sizeof(CClientToMgr) == 0xE8);
    static auto g_pClientToMgr = (CClientToMgr*)0x10A2540; // 0x587968 (session)
}
