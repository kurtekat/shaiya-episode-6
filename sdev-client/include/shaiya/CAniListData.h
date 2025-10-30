#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CAniListData
    {
        PAD(32);
        // 0x20
    };
    #pragma pack(pop)

    static_assert(sizeof(CAniListData) == 0x20);
}
