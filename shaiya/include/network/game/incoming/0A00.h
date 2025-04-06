#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_EXC_REQUEST
    struct GameExchangeRequestIncoming
    {
        uint16_t opcode{ 0xA01 };
        uint32_t targetId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_EXC_READY
    struct GameExchangeReadyIncoming
    {
        uint16_t opcode{ 0xA05 };
        bool canceled;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameExchangeConfirmIncoming
    {
        uint16_t opcode{ 0xA0A };
        bool confirmed;
    };
    #pragma pack(pop)
}
