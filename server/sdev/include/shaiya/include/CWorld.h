#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/SSyncList.h>

namespace shaiya
{
    FWDDECL CMap;
    FWDDECL CUser;
    FWDDECL CZone;
    FWDDECL CZoneNode;

    #pragma pack(push, 1)
    struct InsZoneCount
    {
        UINT32 guildHouse;     //0x368
        UINT32 guildRank;      //0x36C
        UINT32 guildHouseMax;  //0x370
        UINT32 guildRankMax;   //0x374
        UINT32 party;          //0x378
        UINT32 partyMax;       //0x37C
        UINT32 all;            //0x380
        // 0x1C
    };

    struct WorldKCStatus
    {
        UINT32 index;      //0x00
        UINT32 killCount;  //0x04
        UINT32 nextGrade;  //0x08
        PAD(120);
        // 0x84
    };

    struct CWorld
    {
        UINT32 zoneCount;             //0x00
        CZoneNode* zoneNode;          //0x04
        UINT32 mapCount;              //0x08
        PAD(4);
        CRITICAL_SECTION cs10;        //0x10
        // 0x28
        PAD(172);
        UINT32 userCount;             //0xD4
        PAD(88);
        SSyncList<CUser> userList;    //0x130
        PAD(44);
        SSyncList<CUser> waitList;    //0x188
        CRITICAL_SECTION cs1B4;       //0x1B4
        // 0x1CC
        PAD(116);
        ULONG worldDay;               //0x240
        TickCount setWorldDayTime;    //0x244
        // 0x248
        Array<WorldKCStatus, 2> kcStatus;
        CRITICAL_SECTION cs350;       //0x350
        InsZoneCount insZoneCount;    //0x368
        // 0x384

        static CUser* FindUser(ULONG id/*CUser->id*/);
        static CUser* FindUser(const char* charName/*eax*/);
        static int GetUserCount();
        static CZone* GetZone(int mapId/*eax*/);
        static ULONG GetWorldDay();
        static void SendAll(void* data/*ecx*/, int len/*eax*/);
        static void SendAllCountry(void* data/*ecx*/, int len/*eax*/, int country);
        static void SetWorldDay(ULONG time/*eax*/);
    };
    #pragma pack(pop)

    //0x587960
    static CWorld* g_pWorld = (CWorld*)0x10A2018;
}
