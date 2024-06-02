#pragma once
#include <sdev/include/shaiya/include/SVector.h>
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>

namespace shaiya
{
    enum struct InsZoneId : UINT32
    {
        // boss mobs

        Number1001 = 1001,
        Number1002,
        Number1003,
        Number1004,
        Number1005,
        Number1006,
        Number1007,
        Number1008,
        Number1009,
        Number2000 = 2000,

        // portals

        DeepDesertLight = 1010,
        DeepDesertFury = 1020,
        StableErdeLight = 1011,
        StableErdeFury = 1021,
        PalaionRegnumLight = 1060,
        ValdemarRegnumFury = 1061
    };

    #pragma pack(push, 1)
    struct CDoor
    {
        UINT32 insZoneId;  //0x00
        SVector pos;       //0x04
        ULONG id;          //0x10
        Country2 country;  //0x14
        UINT32 minLevel;   //0x18
        UINT32 maxLevel;   //0x1C
        UINT32 destMapId;  //0x20
        SVector destPos;   //0x24
        // 0x30
    };
    #pragma pack(pop)
}
