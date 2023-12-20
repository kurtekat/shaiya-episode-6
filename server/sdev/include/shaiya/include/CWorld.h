#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/Obelisk.h>
#include <include/shaiya/include/SSyncList.h>
#include <include/shaiya/include/SSyncMap.h>

namespace shaiya
{
    struct CDead;
    struct CMap;
    struct CUser;
    struct CZone;
    struct CZoneNode;

    #pragma pack(push, 1)
    struct WorldInsZoneCount
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

    struct WorldKillCount
    {
        UINT32 grade;      //0x00
        UINT32 bless;      //0x04
        UINT32 nextGrade;  //0x08
        PAD(4);
        DWORD updateTime;  //0x10
        PAD(112);
        // 0x84
    };

    struct CWorld
    {
        UINT32 zoneCount;                        //0x00
        CZoneNode* zoneNode;                     //0x04
        UINT32 mapCount;                         //0x08
        PAD(4);
        SSyncMap<ULONG, CUser*> userMap1;        //0x10
        SSyncMap<const char*, CUser*> userMap2;  //0x58
        SSyncMap<ULONG, CUser*> billMap1;        //0xA0
        SSyncMap<const char*, CUser*> billMap2;  //0xE8
        SSyncList<CUser> list130;                //0x130
        SSyncList<CUser> leaveList;              //0x15C
        SSyncList<CUser> waitList;               //0x188
        SSyncList<CDead> deadList;               //0x1B4
        // 0x1CC
        PAD(116);
        ULONG worldDay;                          //0x240
        DWORD setWorldDayTime;                   //0x244
        // AoL, UoF
        Array<WorldKillCount, 2> killCount;      //0x248
        CRITICAL_SECTION cs350;                  //0x350
        WorldInsZoneCount insZoneCount;          //0x368
        // 0x384
        PAD(2204);
        Array<Obelisk::Zone, 64> obeliskZone;    //0xC20
        Array<Obelisk::Boss, 64> obeliskBoss;    //0x824E20
        // 0x3F93038 (end)

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

    // 0x587960
    static CWorld* g_pWorld = (CWorld*)0x10A2018;
}
