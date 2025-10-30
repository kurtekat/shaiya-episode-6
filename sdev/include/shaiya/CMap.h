#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>
#include "CBitArray.h"
#include "MapCurse.h"
#include "MapOpenTime.h"
#include "MapPos.h"
#include "MapWeather.h"
#include "MobRespawn.h"
#include "SVector.h"

namespace shaiya
{
    struct CZone;
    struct MapBind;
    struct MapBoss;
    struct MapDoor;
    struct MobInfo;
    struct MapMob;
    struct MapNpc;
    struct MapObelisk;
    struct MapOther;
    struct MapPortal;
    struct MapSadari;

    enum struct MapCreateType : int32_t
    {
        Dungeon,    // D
        Static,     // S
        Field,      // F
        Party,      // P
        Guild,      // G
        Restricted, // R
        House       // H
    };

    enum struct MapType : int32_t
    {
        Dungeon, // D
        Field    // F
    };

    enum struct WarType : int32_t
    {
        Default,
        Peace    // P
    };

    #pragma pack(push, 1)
    struct CMap
    {
        CZone* zone;               //0x00
        int32_t size;              //0x04
        CBitArray tile;            //0x08
        int32_t mobCount;          //0x14
        MapMob* mobs;              //0x18
        int32_t bossMobCount;      //0x1C
        MapBoss* bosses;           //0x20
        MapWeather weather;        //0x24
        int32_t npcCount;          //0x40
        MapNpc* nps;               //0x44
        int32_t gmNpcCount;        //0x48
        MapNpc* gmNpcs;            //0x4C
        int32_t portalCount;       //0x50 
        MapPortal* portals;        //0x54
        int32_t bindCount;         //0x58
        MapBind* bindings;         //0x5C
        int32_t ladderCount;       //0x60
        MapSadari* ladders;        //0x64
        int32_t doorCount;         //0x68
        MapDoor* doors;            //0x6C
        int32_t otherCount;        //0x70
        MapOther* others;          //0x74
        int32_t id;                //0x78
        WarType warType;           //0x7C
        MapType mapType;           //0x80
        // e.g., 0.svmap
        String<256> name;          //0x84
        MapPos rebirthPos1;        //0x184
        MapPos rebirthPos2;        //0x194
        MapCreateType createType;  //0x1A4
        // 0x1A8
        Array<MapOpenTime, 7> openTimes;
        PAD(2);
        // value * 60000 + 30000
        int32_t expireTime;        //0x1D4
        int32_t createMinUser;     //0x1D8
        int32_t enterMaxUser;      //0x1DC
        bool32_t enableMarket;     //0x1E0
        MapCurse curse;            //0x1E4
        // 0x1EC
        PAD(4);
        double expMultiplier;      //0x1F0
        uint32_t pvpKillAdd;       //0x1F8
        bool obeliskResetSend;     //0x1FC
        PAD(3);
        int32_t obeliskCount;      //0x200
        MapObelisk* obelisks;      //0x200
        // 0x208
    };
    #pragma pack(pop)

    static_assert(sizeof(CMap) == 0x208);
}
