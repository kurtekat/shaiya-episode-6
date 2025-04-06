#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct MapPos
    {
        int32_t mapId;
        float x;
        float y;
        float z;
        // 0x10
    };
    #pragma pack(pop)

    static_assert(sizeof(MapPos) == 0x10);
}
