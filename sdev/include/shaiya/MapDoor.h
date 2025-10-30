#pragma once
#include <shaiya/include/common.h>
#include "SVector.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct MapDoor
    {
        SVector pos;         //0x00
        bool32_t autoClose;  //0x0C
        int32_t closeTime;   //0x10
        // 0x14
    };
    #pragma pack(pop)

    static_assert(sizeof(MapDoor) == 0x14);
}
