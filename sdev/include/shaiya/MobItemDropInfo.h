#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct MobItemDropInfo
    {
        uint16_t grade;
        PAD(2);
        uint32_t rate;
    };
    #pragma pack(pop)

    static_assert(sizeof(MobItemDropInfo) == 0x8);
}
