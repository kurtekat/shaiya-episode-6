#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct AStar
    {
        PAD(40);
        // 0x28
    };
    #pragma pack(pop)

    static_assert(sizeof(AStar) == 0x28);
}
