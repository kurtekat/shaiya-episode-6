#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TPC_SELECT_SERVER
    struct LoginSelectServerOutgoing
    {
        uint16_t opcode{ 0xA202 };
        uint8_t serverId;
        uint32_t ipv4;
    };
    #pragma pack(pop)
}
