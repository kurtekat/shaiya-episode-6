#pragma once
#include <shaiya/include/common.h>
#include "SVector.h"

namespace shaiya
{
    enum struct MapPortalCountry : int32_t
    {
        Neutral,
        Light,
        Fury
    };

    enum struct MapPortalInvasionCountry : uint16_t
    {
        StableErdeLight = 1010,
        DeepDesertLight = 1011,
        StableErdeFury = 1020,
        DeepDesertFury = 1021,
        PalaionRegnumLight = 1060,
        ValdemarRegnumFury = 1061,
        OpalusFury = 1065,
        OpalusLight = 1066
    };

    #pragma pack(push, 1)
    struct MapPortal
    {
        int32_t id;        //0x00
        SVector pos;       //0x04
        // 0x10
        MapPortalCountry baseCountry;
        // 0x14
        MapPortalCountry country;
        int32_t minLevel;  //0x18
        int32_t maxLevel;  //0x1C
        int32_t mapId;     //0x20
        float destX;       //0x24
        float destY;       //0x28
        float destZ;       //0x2C
        // 0x30
    };
    #pragma pack(pop)

    static_assert(sizeof(MapPortal) == 0x30);
}
