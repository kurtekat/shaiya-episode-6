#pragma once
#include <sdev/include/shaiya/common.h>

// CConnection::PacketUserConnect

namespace shaiya
{
    #pragma pack(push, 1)
    struct GameLogoutIncoming
    {
        UINT16 opcode{ 0x302 };
        UserId userId;
    };

    struct GameLogoutOutgoing
    {
        UINT16 opcode{ 0x302 };
        UserId userId;
    };
    #pragma pack(pop)
}
