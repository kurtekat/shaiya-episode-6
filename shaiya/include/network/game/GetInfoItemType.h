#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // ITEM_TYPE
    struct GetInfoItemType
    {
        uint8_t type;
        uint8_t typeId;
        uint8_t enchantStep;
    };
    #pragma pack(pop)

    static_assert(sizeof(GetInfoItemType) == 0x3);
}
