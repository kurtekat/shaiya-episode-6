#pragma once
#include <shaiya/include/common.h>
#include "SaveType.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct PointLog
    {
        SaveType saveType;        //0x00
        String<21> productCode;   //0x04
        PAD(3);
        time32_t purchaseDate;    //0x1C
        uint32_t purchasePoints;  //0x20
        // 0x24
    };
    #pragma pack(pop)

    static_assert(sizeof(PointLog) == 0x24);
}
