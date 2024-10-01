#pragma once
#include <shaiya/include/common.h>
#include "include/shaiya/include/SVector.h"

namespace shaiya
{
    struct CDoor;
    struct CZone;
    struct MobInfo;

    #pragma pack(push, 1)
    // aka spawn area
    struct MapBind
    {
        PAD(16);
        // 0x10
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct MapBossMob
    {
        SVector pos;               //0x00
        float radius;              //0x0C
        PAD(4);
        UINT32 count;              //0x14
        Array<UINT32, 16> mobId;   //0x18
        Array<MobInfo*, 16> mobs;  //0x58
        // 0x98
        PAD(148);
        // 0x12C
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // boss mob subsection
    struct MapRandomRespawn
    {
        UINT32 mapId;  //0x11C
        ULONG time;    //0x120
        SVector pos1;  //0x124
        SVector pos2;  //0x130
        SVector pos3;  //0x13C
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct MapBoss
    {
        UINT32 id;                         //0x00
        UINT32 count;                      //0x04
        ULONG cooldown;                    //0x08
        UINT32 portalMapId;                //0x0C
        UINT32 portalInsZoneId;            //0x10
        PAD(4);
        UINT32 changeMobCount;             //0x18
        SVector pos;                       //0x1C
        PAD(12);
        Array<UINT32, 16> mobId;           //0x34
        Array<MobInfo*, 16> mobs;          //0x74
        // 0xB4
        PAD(100);
        BOOL enableRandomRespawn;          //0x118
        MapRandomRespawn randomRespawn;    //0x11C
        Array<MapBossMob, 32> changeMobs;  //0x148
        PAD(4);
        // 0x26CC
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct MapCreateTime
    {
        UINT16 day;
        // 24-hr format
        UINT16 hour;
        // hours
        UINT16 duration;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct MapLadder
    {
        SVector pos;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct MapMob2
    {
        UINT32 mobId;
        UINT32 count;
        PAD(28);
        // 0x24
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct MapMob
    {
        SVector v;      //0x00
        SVector w;      //0x0C
        UINT32 cellX;   //0x18
        UINT32 cellZ;   //0x1C
        UINT32 count;   //0x20
        MapMob2* mobs;  //0x24
        // 0x28
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct MapNamedArea
    {
        SVector v;  //0x00
        SVector w;  //0x0C
        PAD(16);
        // 0x28
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct MapNpc
    {
        UINT32 type;
        UINT32 typeId;
        UINT32 positionCount;
        SVector* positions;
        PAD(4);
        // 0x14
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct MapObelisk
    {
        PAD(112);
        // 0x70
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct MapObeliskMob
    {
        PAD(88);
        // 0x58
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct MapPortal
    {
        UINT32 id;
        enum struct 
            Country : UINT32 {
            Neutral, 
            Light, 
            Fury
        } country;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct MapRebirth
    {
        UINT32 mapId;
        SVector pos;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct MapWeather
    {
        UINT32 state;
        UINT8 power;
        PAD(3);
        UINT32 rate;
        DWORD delay;
        DWORD noneDelay;
        bool update;
        PAD(3);
        DWORD updateTick;
        // 0x1C
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CMap
    {
        CZone* zone;               //0x00
        UINT32 size;               //0x04
        PAD(12);
        UINT32 mobAreaCount;       //0x14
        MapMob* mobAreas;          //0x18
        PAD(8);
        MapWeather weather;        //0x24
        UINT32 npcCount;           //0x40
        MapNpc* npcs;              //0x44
        PAD(8);
        UINT32 portalCount;        //0x50 
        CDoor* portals;            //0x54
        UINT32 spawnAreaCount;     //0x58
        MapBind* spawnAreas;       //0x5C
        UINT32 ladderCount;        //0x60
        MapLadder* ladders;        //0x64
        PAD(8);
        UINT32 namedAreaCount;     //0x70
        MapNamedArea* namedAreas;  //0x74
        ULONG id;                  //0x78
        enum struct 
            WarType : UINT32 {
            Default, 
            Peace    // P
        } warType;                 //0x7C
        enum struct 
            MapType : UINT32 {
            Dungeon, // D
            Field    // F
        } mapType;                 //0x80
        CharArray<256> svMapName;  //0x84
        MapRebirth rebirth1;       //0x184
        MapRebirth rebirth2;       //0x194
        enum struct 
            CreateType : UINT32 {
            Dungeon,    // D
            Static,     // S
            Field,      // F
            Party,      // P
            Guild,      // G
            Restricted, // R
            House       // H
        } createType;              //0x1A4
        MapCreateTime createTime;  //0x1A8
        PAD(38);
        // value * 60000 + 30000
        ULONG expireTime;          //0x1D4
        UINT32 minUserCount;       //0x1D8
        UINT32 maxUserCount;       //0x1DC
        PAD(40);
        // 0x208

        static CDoor* GetPortal(CMap* map/*ecx*/, int index/*eax*/);
        static CDoor* GetPortalById(CMap* map/*ecx*/, int id/*edi*/);
        static bool IsStatic(CMap* map/*ecx*/);
    };
    #pragma pack(pop)

    static_assert(sizeof(CMap) == 0x208);
}
