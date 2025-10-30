#pragma once
#include <shaiya/include/common.h>
#include "SConnectionTServerReconnect.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CClientToMgr : SConnectionTServerReconnect
    {
        bool connectionReady;  //0xE0
        PAD(7);
        // 0xE8
    };
    #pragma pack(pop)

    static_assert(sizeof(CClientToMgr) == 0xE8);
    static auto g_pClientToMgr = (CClientToMgr*)0x10A2540; // 0x587968 (session)
}
