#pragma once
#include <shaiya/common.h>
#include <shaiya/include/SVector.h>

namespace shaiya
{
    FWDDECL CDoor;

    #pragma pack(push, 1)
    enum struct WarType : UINT32
    {
        Default,
        Peace    // P
    };

    enum struct MapType : UINT32
    {
        Dungeon, // D
        Field    // F
    };

    enum struct CreateType : UINT32
    {
        Dungeon,    // D
        Static,     // S
        Field,      // F
        Party,      // P
        Guild,      // G
        Restricted, // R
        House       // H
    };

    struct Rebirth
    {
        UINT32 mapId;
        SVector pos;
    };

    struct CMap
    {
        PAD(4);
        UINT32 size;             //0x04
        PAD(12);
        Count mobAreas;          //0x14
        PAD(12);
        UINT32 weatherState;     //0x24
        UINT32 weatherPower;     //0x28
        UINT32 weatherRate;      //0x2C
        // value * 60000
        ULONG weatherDelay;      //0x30
        // value * 60000
        ULONG weatherNoneDelay;  //0x34
        PAD(8);
        Count npcs;              //0x40
        PAD(12);
        Count portals;           //0x50
        CDoor* portal;           //0x54
        Count spawnAreas;        //0x58
        PAD(4);
        Count ladders;           //0x60
        PAD(12);
        Count namedAreas;        //0x70
        PAD(4);
        ULONG id;                //0x78
        WarType warType;         //0x7C
        MapType mapType;         //0x80
        char svMapName[256];     //0x84
        Rebirth rebirth1;        //0x184
        Rebirth rebirth2;        //0x194
        CreateType createType;   //0x1A4
        short createTime[3];     //0x1A8
        PAD(38);
        // value * 60000 + 30000
        TickCount expireTime;    //0x1D4
        Count minUsers;          //0x1D8
        Count maxUsers;          //0x1DC
        PAD(40);
        // 0x208

        static CDoor* GetPortal(CMap* map/*ecx*/, int index/*eax*/);
        static CDoor* GetPortalById(CMap* map/*ecx*/, int insZoneId/*edi*/);
        static bool IsStatic(CMap* map/*ecx*/);
    };
    #pragma pack(pop)
}
