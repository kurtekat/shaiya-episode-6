#pragma once
#include <shaiya/include/common.h>
#include "SaveType.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct SavePoint
    {
        SaveType saveType;  //0x00
        uint16_t mapId;     //0x04
        PAD(2);
        float x;            //0x08
        float y;            //0x0C
        float z;            //0x10
        // 0x14
    };
    #pragma pack(pop)

    static_assert(sizeof(SavePoint) == 0x14);
}
