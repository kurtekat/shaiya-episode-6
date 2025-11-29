#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct RewardItem
    {
        uint8_t type;
        uint8_t typeId;
        uint8_t count;
        PAD(1);
        uint32_t minutes;
    };
    #pragma pack(pop)

    static_assert(sizeof(RewardItem) == 0x8);
}
