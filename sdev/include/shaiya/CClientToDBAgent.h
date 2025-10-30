#pragma once
#include <shaiya/include/common.h>
#include "SConnectionTServerReconnect.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CClientToDBAgent : SConnectionTServerReconnect
    {
        bool connectionReady;  //0xE0
        PAD(7);
        // 0xE8
    };
    #pragma pack(pop)

    static_assert(sizeof(CClientToDBAgent) == 0xE8);
    static auto g_pClientToDBAgent = (CClientToDBAgent*)0x10A2628; // 0x58796C
}
