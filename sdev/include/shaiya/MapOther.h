#pragma once
#include <shaiya/include/common.h>
#include "SBoxAxis.h"

namespace shaiya
{
    #pragma pack(push, 1)
    // named area
    struct MapOther
    {
        SBoxAxis area;  //0x00
        int32_t type;   //0x18
        int32_t attr1;  //0x1C
        int32_t attr2;  //0x20
        int32_t attr3;  //0x24
        // 0x28
    };
    #pragma pack(pop)

    static_assert(sizeof(MapOther) == 0x28);
}
