#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ExcItem
    {
        uint8_t bag;
        uint8_t slot;
        uint8_t count;
    };
    #pragma pack(pop)

    static_assert(sizeof(ExcItem) == 0x3);
}
