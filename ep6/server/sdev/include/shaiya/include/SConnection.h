#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    FWDDECL CUser;

    #pragma pack(push, 1)
    struct SConnection
    {
        PAD(104);
        Socket socket;   //0x68
        PAD(4);
        ULONG ipv4Addr;  //0x70
        PAD(92);
        // 0xD0

        static void Send(CUser* user/*ecx*/, void* buf, int len);
        static void Close(CUser* user/*ecx*/, int closeType, int closeErr);
    };
    #pragma pack(pop)
}
