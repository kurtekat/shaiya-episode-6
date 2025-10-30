#pragma once
#include <shaiya/include/common.h>
#include "SVector.h"

namespace shaiya
{
    #pragma pack(push, 1)
    // ladder
    struct MapSadari
    {
        SVector pos;
    };
    #pragma pack(pop)

    static_assert(sizeof(MapSadari) == 0xc);
}
