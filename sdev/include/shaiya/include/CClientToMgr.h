#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/SConnection.h>

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

    // 0x587968 (session)
    static auto g_pClientToMgr = (CClientToMgr*)0x10A2540;
}
