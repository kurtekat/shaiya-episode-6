#pragma once
#include <sdev/include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SConnection
    {
        PAD(24);
        int closeType;   //0x18
        int closeErr;    //0x1C
        PAD(72);
        int socket;      //0x68
        PAD(4);
        ULONG ipv4Addr;  //0x70
        PAD(92);
        // 0xD0

        static void Send(SConnection* connection/*ecx*/, void* buf, int len);
        static void Close(SConnection* connection/*ecx*/, int closeType, int closeErr);
        static bool IsConnected(SConnection* connection/*ecx*/);
    };
    #pragma pack(pop)
}
