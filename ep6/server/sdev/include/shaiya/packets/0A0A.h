#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ConfirmExchangeRequest
    {
        UINT16 opcode; // 0xA0A
        UINT8 state;
    };

    struct ConfirmExchangeResponse
    {
        UINT16 opcode; // 0xA0A
        UINT8 state1;
        UINT8 state2;
    };
    #pragma pack(pop)
}
