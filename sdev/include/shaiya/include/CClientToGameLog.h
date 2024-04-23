#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/SConnection.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CClientToGameLog
    {
        SConnection connection;  //0x00
        PAD(16);
        // 0xE0
    };
    #pragma pack(pop)

    // 0x587974
    static auto g_pClientToGameLog = (CClientToGameLog*)0x10A2818;
}
