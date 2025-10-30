#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct Quick
    {
        uint8_t quickBar;
        uint8_t quickSlot;
        uint8_t bag;
        PAD(1);
        uint16_t number;
        // 0x6
    };
    #pragma pack(pop)

    static_assert(sizeof(Quick) == 0x6);
}
