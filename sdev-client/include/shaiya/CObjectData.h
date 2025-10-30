#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CObjectData
    {
        PAD(28);
        // 0x1C
    };
    #pragma pack(pop)

    static_assert(sizeof(CObjectData) == 0x1C);
}
