#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/SVector.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct Obelisk
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

        enum struct Country : UINT32
        {
            Neutral,
            Light,
            Fury
        };

        struct Mob
        {
            SVector pos;              //0x00
            float radius;             //0x0C
            PAD(4);
            UINT32 count;             //0x14
            Array<UINT32, 16> mobId;  //0x18
            // 0x58
            PAD(212);
            // 0x12C
        };

        // boss mob subsection
        struct RandomRespawn
        {
            UINT32 mapId;  //0x11C
            ULONG time;    //0x120
            SVector pos1;  //0x124
            SVector pos2;  //0x130
            SVector pos3;  //0x13C
        };

        struct BossMob
        {
            UINT32 id;                    //0x00
            UINT32 count;                 //0x04
            UINT32 respawnTime;           //0x08
            UINT32 portalMapId;           //0x0C
            InsZoneId portalInsZoneId;    //0x10
            PAD(4);
            UINT32 changeMobCount;        //0x18
            SVector pos;                  //0x1C
            PAD(12);
            Array<UINT32, 15> mobId;      //0x34
            // 0x70
            PAD(168);
            BOOL enableRandomRespawn;     //0x118
            RandomRespawn randomRespawn;  //0x11C
            Array<Mob, 32> changeMob;     //0x148
            PAD(4);
            // 0x26CC
        };

        // 0x18C6E38
        struct Boss
        {
            UINT32 mapId;                //0x00
            UINT32 bossMobCount;         //0x04
            Array<BossMob, 64> bossMob;  //0x08
            // 0x9B308
        };

        struct PortalRelic
        {
            UINT32 mapId;
            UINT32 id;
        };

        // 0x5845C0
        struct Portal
        {
            UINT8 id;                     //0x00
            PAD(3);
            UINT32 mapId;                 //0x04
            InsZoneId insZoneId;          //0x08
            Array<PortalRelic, 8> relic;  //0x0C
            // 0x4C
        };

        struct RelicMob
        {
            SVector pos;          //0x00
            float radius;         //0x0C
            UINT32 neutralMobId;  //0x10
            UINT32 lightMobId;    //0x14
            UINT32 furyMobId;     //0x18
            UINT32 count;         //0x1C
            // 0x20
        };

        struct Relic
        {
            UINT32 id;                //0x00
            PAD(4);
            SVector pos;              //0x08
            UINT32 neutralMobId;      //0x14
            UINT32 lightMobId;        //0x18
            UINT32 furyMobId;         //0x1C
            UINT32 mobCount;          //0x20
            Array<RelicMob, 64> mob;  //0x24
            // 0x824
        };

        // 0x10A2C38
        struct Zone
        {
            UINT32 id;               //0x00
            UINT32 relicCount;       //0x04
            Array<Relic, 64> relic;  //0x08
            // 0x20908
        };
    };
    #pragma pack(pop)
}
