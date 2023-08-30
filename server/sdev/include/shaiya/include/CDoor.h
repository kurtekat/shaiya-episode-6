#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/SVector.h>

namespace shaiya
{
    #pragma pack(push, 1)
    enum struct PortalCountry : UINT32
    {
        Neutral,
        Light,
        Fury,
    };

    enum PortalInsZoneId
    {
        DeepDesertLight = 1010,
        DeepDesertFury = 1020,
        StableErdeLight = 1011,
        StableErdeFury = 1021,
        PalaionRegnumLight = 1060,
        ValdemarRegnumFury = 1061
    };

    struct CDoor
    {
        UINT32 insZoneId;       //0x00
        SVector pos;            //0x04
        ULONG id;               //0x10
        PortalCountry country;  //0x14
        UINT32 minLevel;        //0x18
        UINT32 maxLevel;        //0x1C
        UINT32 outMapId;        //0x20
        SVector outPos;         //0x24
        // 0x30
    };
    #pragma pack(pop)
}
