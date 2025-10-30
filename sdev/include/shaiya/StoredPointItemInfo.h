#pragma once
#include <shaiya/include/common.h>
#include "BillingItemInfo.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct StoredPointItemInfo : BillingItemInfo
    {
    };
    #pragma pack(pop)

    static_assert(sizeof(StoredPointItemInfo) == 0x3);
}
