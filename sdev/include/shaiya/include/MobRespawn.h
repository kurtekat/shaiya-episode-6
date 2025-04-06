#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    struct MapBossMob;
    struct MapObeliskMob;
    struct MobInfo;

    #pragma pack(push, 1)
    struct MobRespawn
    {
        int32_t mobId;         //0x00
        int32_t count;         //0x04
        int32_t currentCount;  //0x08
        uint32_t respawnTime;  //0x0C
        MobInfo* mobInfo;      //0x10
        bool isObelisk;        //0x14
        PAD(3);
        // 0x18
        MapObeliskMob* obeliskMob;
        bool isBossMob;        //0x1C
        PAD(3);
        MapBossMob* bossMob;   //0x20
        // 0x24
    };
    #pragma pack(pop)

    static_assert(sizeof(MobRespawn) == 0x24);
}
