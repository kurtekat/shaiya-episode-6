#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct Packet1B01Incoming
    {
        UINT16 opcode{ 0x1B01 };
        UserId userId;
        ULONG ipv4Addr;
    };
    #pragma pack(pop)
}
