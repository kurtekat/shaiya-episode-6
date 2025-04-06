#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct DBAgentQuickUnit
    {
        uint8_t quickBar;
        uint8_t quickSlot;
        uint8_t bag;
        uint16_t number;
    };
    #pragma pack(pop)
}
