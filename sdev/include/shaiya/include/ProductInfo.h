#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ProductInfo
    {
        ProductCode productCode;     //0x00
        PAD(3);
        Array<UINT32, 24> itemId;    //0x18
        Array<UINT8, 24> itemCount;  //0x78
        UINT32 price;                //0x90
        Array<char, 51> productName; //0x94
        PAD(1);
        // 0xC8
    };
    #pragma pack(pop)
}
