#pragma once
#include <array>
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>
#include "include/shaiya/include/SVector.h"

namespace shaiya
{
    struct CDoor;
    struct MobInfo;

    using SvMapName = std::array<char, 256>;

    enum struct MapCreateType : UINT32
    {
        Dungeon,    // D
        Static,     // S
        Field,      // F
        Party,      // P
        Guild,      // G
        Restricted, // R
        House       // H
    };

    enum struct MapType : UINT32
    {
        Dungeon, // D
        Field    // F
    };

    enum struct MapWarType : UINT32
    {
        Default,
        Peace    // P
    };

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
        SVector pos;   //0x00
        float radius;  //0x0C
        PAD(4);
        UINT32 count;  //0x14
        // 0x18
        std::array<UINT32, 16> mobId;
        // 0x58
        std::array<MobInfo*, 16> mobList;
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
        UINT32 id;                 //0x00
        UINT32 count;              //0x04
        UINT32 respawnTime;        //0x08
        UINT32 portalMapId;        //0x0C
        UINT32 portalInsZoneId;    //0x10
        PAD(4);
        UINT32 changeMobCount;     //0x18
        SVector pos;               //0x1C
        PAD(12);
        // 0x34
        std::array<UINT32, 16> mobId;
        // 0x74
        std::array<MobInfo*, 16> mobList;
        // 0xB4
        PAD(100);
        BOOL enableRandomRespawn;  //0x118
        // 0x11C
        MapRandomRespawn randomRespawn;
        // 0x148
        std::array<MapBossMob, 32> changeMobList;
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
        // 0xC
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
        SVector v;         //0x00
        SVector w;         //0x0C
        UINT32 cellX;      //0x18
        UINT32 cellZ;      //0x1C
        UINT32 count;      //0x20
        MapMob2* mobList;  //0x24
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
        UINT32 posCount;
        SVector* posList;
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
        Country2 country;
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
        DWORD updateTime;
        // 0x1C
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CMap
    {
        PAD(4);
        UINT32 size;               //0x04
        PAD(12);
        UINT32 mobAreaCount;       //0x14
        MapMob* mobAreaList;       //0x18
        PAD(8);
        MapWeather weather;        //0x24
        UINT32 npcCount;           //0x40
        MapNpc* npcList;           //0x44
        PAD(8);
        UINT32 portalCount;        //0x50 
        CDoor* portalList;         //0x54
        UINT32 bindCount;          //0x58
        MapBind* bindList;         //0x5C
        UINT32 ladderCount;        //0x60
        MapLadder* ladderList;     //0x64
        PAD(8);
        UINT32 namedAreaCount;     //0x70
        // 0x74
        MapNamedArea* namedAreaList;
        ULONG id;                  //0x78
        MapWarType warType;        //0x7C
        MapType mapType;           //0x80
        SvMapName svMapName;       //0x84
        MapRebirth rebirth1;       //0x184
        MapRebirth rebirth2;       //0x194
        MapCreateType createType;  //0x1A4
        MapCreateTime createTime;  //0x1A8
        PAD(38);
        // value * 60000 + 30000
        DWORD expireTime;          //0x1D4
        UINT32 minUserCount;       //0x1D8
        UINT32 maxUserCount;       //0x1DC
        PAD(40);
        // 0x208

        static CDoor* GetPortal(CMap* map/*ecx*/, int index/*eax*/);
        static CDoor* GetPortalById(CMap* map/*ecx*/, int id/*edi*/);
        static bool IsStatic(CMap* map/*ecx*/);
    };
    #pragma pack(pop)
}
