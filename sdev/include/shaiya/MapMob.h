#pragma once
#include <shaiya/include/common.h>
#include "SBoxAxis.h"

namespace shaiya
{
    struct MobRespawn;

    #pragma pack(push, 1)
    struct MapMob
    {
        SBoxAxis area;        //0x00
        int32_t deltaX;       //0x18
        int32_t deltaZ;       //0x1C
        int32_t count;        //0x20
        MobRespawn* respawn;  //0x24
        // 0x28
    };
    #pragma pack(pop)

    static_assert(sizeof(MapMob) == 0x28);
}
