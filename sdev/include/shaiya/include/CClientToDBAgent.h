#pragma once
#include <shaiya/include/common.h>
#include "include/shaiya/include/SConnection.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CClientToDBAgent
    {
        SConnection connection;  //0x00
        PAD(8);
        bool connected;          //0xD8
        PAD(15);
        // 0xE8
    };
    #pragma pack(pop)

    static_assert(sizeof(CClientToDBAgent) == 0xE8);
    static auto g_pClientToDBAgent = (CClientToDBAgent*)0x10A2628; // 0x58796C
}
