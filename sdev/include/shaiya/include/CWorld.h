#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/SSyncList.h>
#include <shaiya/include/common/SSyncMap.h>

namespace shaiya
{
    struct CDead;
    struct CMap;
    struct CUser;
    struct CZone;
    struct CZoneNode;

    #pragma pack(push, 1)
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
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CWorld
    {
        UINT32 zoneCount;                         //0x00
        CZoneNode* zoneNode;                      //0x04
        UINT32 mapCount;                          //0x08
        PAD(4);
        SSyncMap<ULONG, CUser*> users1;           //0x10
        SSyncMap<const char*, CUser*> users2;     //0x58
        SSyncMap<ULONG, CUser*> users3;           //0xA0
        SSyncMap<const char*, CUser*> users4;     //0xE8
        SSyncList<CUser> userList1;               //0x130
        SSyncList<CUser> userList2;               //0x15C
        SSyncList<CUser> userList3;               //0x188
        SSyncList<CDead> deadList;                //0x1B4
        // 0x1CC
        PAD(116);
        ULONG worldDay;                           //0x240
        DWORD setWorldDayTime;                    //0x244
        // AoL, UoF
        std::array<WorldKillCount, 2> killCount;  //0x248
        CRITICAL_SECTION cs350;                   //0x350
        UINT32 guildHouseCount;                   //0x368
        UINT32 guildRankCount;                    //0x36C
        UINT32 guildHouseMaxCount;                //0x370
        UINT32 guildRankMaxCount;                 //0x374
        UINT32 partyCount;                        //0x378
        UINT32 partyMaxCount;                     //0x37C
        UINT32 allCount;                          //0x380
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

    // 0x587960
    static auto g_pWorld = (CWorld*)0x10A2018;
}
