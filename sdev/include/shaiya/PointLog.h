#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
   #pragma pack(push, 1)
    struct PointLog
    {
        String<21> productCode;   //0x00
        PAD(3);
        time32_t purchaseDate;    //0x18
        uint32_t purchasePoints;  //0x1C
        // 0x20
    };
    #pragma pack(pop)

    static_assert(sizeof(PointLog) == 0x20);
}
