#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    typedef Array<char, 25> ItemKey;
    typedef Array<char, 16> OrderNumber;

    #pragma pack(push, 1)
    struct Packet1B01Incoming
    {
        UINT16 opcode{ 0x1B01 };
        UserId userId;
        ULONG ipv4Addr;
    };

    // CClientToMgr::OnRecv
    // ebx = packet
    // handler: 0x40716A

    struct PacketBuffer1B01
    {
        ULONG u0x00;
        void* p0x04{ &u0x0C };
        ULONG u0x08;
        ULONG u0x0C{ 0x1B010000 };
        UserId userId;  // ebx+0x02
        UINT8 result;   // ebx+0x06
        UINT32 points;  // ebx+0x07
        // 0x0B
    };

    // CClientToMgr::OnRecv
    // ebx = packet
    // handler: 0x407386

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

    // CClientToMgr::OnRecv
    // ebx = packet
    // handler: 0x407216

    struct PacketBuffer1B03
    {
        ULONG u0x00;
        void* p0x04{ &u0x0C };
        ULONG u0x08;
        ULONG u0x0C{ 0x1B030000 };
        UserId userId;            // ebx+0x02
        ProductCode productCode;  // ebx+0x06
        CharName targetName;      // ebx+0x1B
        UINT32 itemPrice;         // ebx+0x30
        UINT32 points;            // ebx+0x34
        // 0x46
    };
    #pragma pack(pop)
}
