#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_POINTITEM_UNIT
    struct PointItemUnit_EP5
    {
        uint8_t bag;
        uint8_t slot;
        uint8_t type;
        uint8_t typeId;
        uint8_t count;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_POINTITEM_UNIT
    struct PointItemUnit_EP6_4
    {
        uint8_t bag;
        uint8_t slot;
        uint8_t type;
        uint8_t typeId;
        uint8_t count;
        time32_t fromDate;
        time32_t toDate;
    };
    #pragma pack(pop)
}
