#pragma once
#include <shaiya/include/common.h>
#include "CObject.h"
#include "SBoxAxis.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CMapRegion : CObject
    {
        SBoxAxis area;   //0x28
        int type;        //0x40
        int32_t value1;  //0x44
        int32_t value2;  //0x48
        int32_t value3;  //0x4C
        // 0x50
    };
    #pragma pack(pop)

    static_assert(sizeof(CMapRegion) == 0x50);
}
