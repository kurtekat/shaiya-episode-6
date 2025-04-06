#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct BillingItemInfo
    {
        uint8_t type;
        uint8_t typeId;
        uint8_t count;
    };
    #pragma pack(pop)

    static_assert(sizeof(BillingItemInfo) == 0x3);
}
