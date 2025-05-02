#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_POINTLOG_UNIT
    struct PointLogUnit
    {
        String<21> productCode;
        time32_t purchaseDate;
        uint32_t purchasePoints;
    };
    #pragma pack(pop)
}
