#pragma once
#include <shaiya/include/common.h>
#include "SBoxAxis.h"

namespace shaiya
{
    #pragma pack(push, 1)
    // spawn area
    struct MapBind
    {
        int32_t count;    //0x00
        int32_t country;  //0x04
        int32_t attr;     //0x08
        SBoxAxis area;    //0x0C
        // 0x24
    };
    #pragma pack(pop)

    static_assert(sizeof(MapBind) == 0x24);
}
