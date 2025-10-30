#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ExcItem
    {
        uint8_t srcBag;
        uint8_t srcSlot;
        uint8_t count;
    };
    #pragma pack(pop)

    static_assert(sizeof(ExcItem) == 0x3);
}
