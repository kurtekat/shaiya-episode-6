#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common.h>
#include <shaiya/include/common/SConnection.h>
#include <shaiya/include/user/Password.h>
#include <shaiya/include/user/Username.h>

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
        Username username;       //0x3C0
        Password password;       //0x3E0
        CRITICAL_SECTION cs400;  //0x400
        // 0x418
    };
    #pragma pack(pop)
}
