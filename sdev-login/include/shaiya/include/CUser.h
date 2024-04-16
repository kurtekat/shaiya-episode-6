#pragma once
#include <sdev/include/shaiya/common.h>
#include <sdev/include/shaiya/include/SConnection.h>

namespace shaiya
{
    struct CUser
    {
        SConnection connection;  //0x00
        // 0xD0
        PAD(12);
        CRITICAL_SECTION csDC;   //0xDC
        // 0xF4
        PAD(12);
        UserId userId;           //0x100
        PAD(700);
        Username username;       //0x3C0
        Password password;       //0x3E0
        CRITICAL_SECTION cs400;  //0x400
        // 0x418
    };
    #pragma pack(pop)
}
