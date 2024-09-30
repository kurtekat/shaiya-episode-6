#pragma once
#include <shaiya/include/common.h>
#include "include/shaiya/include/SConnection.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CClientToGameLog
    {
        SConnection connection;  //0x00
        PAD(8);
        bool connected;          //0xD8
        PAD(7);
        // 0xE0
    };
    #pragma pack(pop)

    static_assert(sizeof(CClientToGameLog) == 0xE0);
    static auto g_pClientToGameLog = (CClientToGameLog*)0x10A2818; // 0x587974
}
