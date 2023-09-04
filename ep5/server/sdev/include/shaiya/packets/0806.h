#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    enum struct ItemComposeResult : UINT8
    {
        Success,
        Failure
    };

    struct ItemComposeResponse
    {
        UINT16 opcode; // 0x806
        ItemComposeResult result;
        UINT8 bag;
        UINT8 slot;
        char craftName[21];
    };
    #pragma pack(pop)
}
