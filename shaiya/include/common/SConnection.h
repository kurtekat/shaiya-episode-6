#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SConnection
    {
        PAD(24);
        int closeType;          //0x18
        int closeErr;           //0x1C
        PAD(48);
        CRITICAL_SECTION cs50;  //0x50
        int socket;             //0x68
        PAD(4);
        ULONG ipv4Addr;         //0x70
        PAD(16);
        CRITICAL_SECTION cs84;  //0x84
        // 0x9C
        PAD(16);
        CRITICAL_SECTION csAC;  //0xAC
        // 0xC4
        PAD(12);
        // 0xD0

        static void Send(SConnection* connection/*ecx*/, void* buf, int len);
        static void Close(SConnection* connection/*ecx*/, int closeType, int closeErr);
        static bool IsConnected(SConnection* connection/*ecx*/);
    };
    #pragma pack(pop)
}
