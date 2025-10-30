#pragma once
#include <shaiya/include/common.h>
#include "MobRespawn.h"
#include "SVector.h"

namespace shaiya
{
    struct CMob;
    struct MobInfo;

    #pragma pack(push, 1)
    struct MapBossMob
    {
        SVector center;             //0x00
        float radius;               //0x0C
        int32_t radius2x;           //0x10
        int32_t mobCount;           //0x14
        Array<int32_t, 16> mobIds;  //0x18
        // 0x58
        Array<MobInfo*, 16> mobInfo;
        Array<CMob*, 16> mobs;      //0x98
        MobRespawn respawn;         //0xBC
        bool32_t randomBossMob;     //0xFC
        // 0x100
        uint32_t randomMinRespawnTime;
        // 0x104
        uint32_t randomMaxRespawnTime;
        // 0x108
        Array<SVector, 3> randomCenter;
        // 0x12C
    };
    #pragma pack(pop)

    static_assert(sizeof(MapBossMob) == 0x12C);
}
