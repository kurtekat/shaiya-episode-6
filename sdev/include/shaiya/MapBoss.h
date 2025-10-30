#pragma once
#include <shaiya/include/common.h>
#include "MapBossMob.h"

namespace shaiya
{
    struct MapPortal;

    #pragma pack(push, 1)
    struct MapBoss
    {
        uint32_t id;           //0x00
        int32_t changeCount;   //0x04
        uint32_t respawnTime;  //0x08
        int32_t portalMapId;   //0x0C
        int32_t portalId;      //0x10
        MapPortal* mapPortal;  //0x14
        int32_t mobCount;      //0x18
        MapBossMob bossMob;    //0x1C
        // 0x148
        Array<MapBossMob, 32> mobs;
        int32_t currentIndex;  //0x26C8
        // 0x26CC
    };
    #pragma pack(pop)

    static_assert(sizeof(MapBoss) == 0x26CC);
}
