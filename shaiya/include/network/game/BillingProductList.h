#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct BillingProductList
    {
        String<21> productCode;
        String<51> productName;
        uint32_t buyPoints;
    };
    #pragma pack(pop)
}
