#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    struct SVector;

    #pragma pack(push, 1)
    struct MapNpc
    {
        int32_t type;           //0x00
        int32_t typeId;         //0x04
        int32_t positionCount;  //0x08
        SVector* positions;     //0x0C
        float* angles;          //0x10
        // 0x14
    };
    #pragma pack(pop)

    static_assert(sizeof(MapNpc) == 0x14);
}
