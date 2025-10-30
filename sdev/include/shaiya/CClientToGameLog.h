#pragma once
#include <shaiya/include/common.h>
#include "SConnectionTBaseReconnect.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CClientToGameLog : SConnectionTBaseReconnect
    {
    };
    #pragma pack(pop)

    static_assert(sizeof(CClientToGameLog) == 0xE0);
    static auto g_pClientToGameLog = (CClientToGameLog*)0x10A2818; // 0x587974
}
