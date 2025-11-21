#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct PointItemGift
    {
        String<21> targetName;    //0x00
        String<21> productCode;   //0x21
        PAD(2);
        uint32_t purchasePoints;  //0x2C
        time32_t purchaseDate;    //0x30
        uint32_t purchaseNumber;  //0x34
        // 0x38
    };
    #pragma pack(pop)

    static_assert(sizeof(PointItemGift) == 0x38);
}
