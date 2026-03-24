#pragma once
#include <shaiya/include/common.h>
#include "TargetType.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct Target
    {
        TargetType type;
        uint32_t objectId;
        // 0x8
    };
    #pragma pack(pop)

    static_assert(sizeof(Target) == 0x8);
}
