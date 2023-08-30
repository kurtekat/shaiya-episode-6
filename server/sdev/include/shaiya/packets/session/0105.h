#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    // g_nPayLetterEnable 0x58799C

    #pragma pack(push, 1)
    struct PayLetterEnable
    {
        UINT16 opcode{ 0x105 };
        bool enable;
    };

    // CClientToMgr::OnRecv
    // ebx = packet
    // handler: 0x4069CB

    struct PacketBuffer0105
    {
        ULONG u0x00;
        void* p0x04{ &u0x0C };
        ULONG u0x08;
        ULONG u0x0C{ 0x1050000 };
        bool enable;  // ebx+0x02
        // 0x11
    };
    #pragma pack(pop)
}
