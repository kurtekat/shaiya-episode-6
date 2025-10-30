#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ShopItem
    {
        uint8_t type;
        uint8_t typeId;
    };
    #pragma pack(pop)

    static_assert(sizeof(ShopItem) == 0x2);
}
