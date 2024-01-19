#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/CMap.h>
#include <include/shaiya/include/SVector.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ObeliskMob
    {
        SVector pos;          //0x00
        float radius;         //0x0C
        UINT32 neutralMobId;  //0x10
        UINT32 lightMobId;    //0x14
        UINT32 furyMobId;     //0x18
        UINT32 count;         //0x1C
        // 0x20
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct Obelisk
    {
        UINT32 id;                  //0x00
        PAD(4);
        SVector pos;                //0x08
        UINT32 neutralMobId;        //0x14
        UINT32 lightMobId;          //0x18
        UINT32 furyMobId;           //0x1C
        UINT32 mobCount;            //0x20
        Array<ObeliskMob, 64> mob;  //0x24
        // 0x824
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct Obelisk2
    {
        UINT32 mapId;
        UINT32 id;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // 0x5845C0
    struct ObeliskPortal
    {
        UINT8 id;                    //0x00
        PAD(3);
        UINT32 mapId;                //0x04
        InsZoneId insZoneId;         //0x08
        Array<Obelisk2, 8> obelisk;  //0x0C
        // 0x4C
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // 0x10A2C38
    struct ObeliskZone
    {
        UINT32 id;                   //0x00
        UINT32 obeliskCount;         //0x04
        Array<Obelisk, 64> obelisk;  //0x08
        // 0x20908
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // 0x18C6E38
    struct ObeliskBoss
    {
        UINT32 mapId;                //0x00
        UINT32 bossMobCount;         //0x04
        Array<MapBoss, 64> bossMob;  //0x08
        // 0x9B308
    };
    #pragma pack(pop)
}
