#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct RewardItemUnit
    {
        uint32_t minutes;
        uint8_t type;
        uint8_t typeId;
        uint8_t count;
    };
    #pragma pack(pop)
}
