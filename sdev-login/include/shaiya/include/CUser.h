#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/SConnection.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CUser
    {
        SConnection connection;  //0x00
        // 0xD0
        PAD(12);
        CRITICAL_SECTION csDC;   //0xDC
        // 0xF4
        PAD(12);
        ULONG userId;            //0x100
        PAD(36);
        UINT64 sessionId;        //0x128
        PAD(8);
        UINT8 serverId;          //0x138
        PAD(647);
        CharArray<32> username;  //0x3C0
        CharArray<32> password;  //0x3E0
        CRITICAL_SECTION cs400;  //0x400
        // 0x418
    };
    #pragma pack(pop)
}
