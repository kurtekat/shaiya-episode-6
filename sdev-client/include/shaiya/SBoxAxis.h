#pragma once
#include <shaiya/include/common.h>
#include "common.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct SBoxAxis
    {
        D3DVECTOR min;  //0x00
        D3DVECTOR max;  //0x0C
        // 0x18
    };
    #pragma pack(pop)

    static_assert(sizeof(SBoxAxis) == 0x18);
}
