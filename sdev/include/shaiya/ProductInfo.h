#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ProductInfo
    {
        String<21> productCode;         //0x00
        PAD(3);
        Array<uint32_t, 24> itemIds;    //0x18
        Array<uint8_t, 24> itemCounts;  //0x78
        uint32_t purchasePoints;        //0x90
        String<51> productName;         //0x94
        PAD(1);
        // 0xC8
    };
    #pragma pack(pop)

    static_assert(sizeof(ProductInfo) == 0xC8);
}
