#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CBitArray
    {
        PAD(12);
        // 0xC
    };
    #pragma pack(pop)

    static_assert(sizeof(CBitArray) == 0xC);
}
