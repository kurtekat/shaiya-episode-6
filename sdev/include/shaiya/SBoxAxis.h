#pragma once
#include <shaiya/include/common.h>
#include "SVector.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct SBoxAxis
    {
        SVector min;  //0x00
        SVector max;  //0x0C
        // 0x18
    };
    #pragma pack(pop)

    static_assert(sizeof(SBoxAxis) == 0x18);
}
