#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    using ProductCode = std::array<char, 21>;

    #pragma pack(push, 1)
    struct ProductInfo
    {
        ProductCode productCode;           //0x00
        PAD(3);
        std::array<UINT32, 24> itemId;     //0x18
        std::array<UINT8, 24> itemCount;   //0x78
        UINT32 price;                      //0x90
        std::array<char, 51> productName;  //0x94
        PAD(1);
        // 0xC8
    };
    #pragma pack(pop)
}
