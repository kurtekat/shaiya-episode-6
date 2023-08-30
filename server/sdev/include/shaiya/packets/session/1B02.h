#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    typedef Array<char, 25> ItemKey;
    typedef Array<char, 16> OrderNumber;

    // CClientToMgr::OnRecv
    // ebx = packet
    // handler: 0x407386

    #pragma pack(push, 1)
    struct PacketBuffer1B02
    {
        ULONG u0x00;
        void* p0x04{ &u0x0C };
        ULONG u0x08;
        ULONG u0x0C{ 0x1B020000 };
        UserId userId;     // ebx+0x02
        ULONG charId;      // ebx+0x06
        UINT8 result;      // ebx+0x0A
        ItemKey itemKey;   // ebx+0x0B
        UINT32 u0x32;      // ebx+0x24
        // ebx+0x28
        OrderNumber orderNumber;
        // user->id
        ULONG id;          // ebx+0x38
        UINT32 u0x4A;      // ebx+0x3C
        UINT32 itemCount;  // ebx+0x40
        // 0x52
    };
    #pragma pack(pop)
}
