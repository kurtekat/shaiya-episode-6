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

    #pragma pack(push, 1)
    struct WorldKillCount
    {
        UINT32 grade;      //0x00
        UINT32 bless;      //0x04
        UINT32 nextGrade;  //0x08
        PAD(4);
        DWORD updateTick;  //0x10
        PAD(112);
        // 0x84
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CWorld
    {
        UINT32 zoneCount;                           //0x00
        PAD(4);
        UINT32 mapCount;                            //0x08
        PAD(4);
        SSyncMap<ULONG, CUser*> leaveUsers;         //0x10
        SSyncMap<const char*, CUser*> leaveUsers2;  //0x58
        SSyncMap<ULONG, CUser*> enterUsers;         //0xA0
        SSyncMap<const char*, CUser*> enterUsers2;  //0xE8
        SSyncList<CUser> list130;                   //0x130
        SSyncList<CUser> list15C;                   //0x15C
        SSyncList<CUser> list188;                   //0x188
        SSyncList<CDead> list1B4;                   //0x1B4
        // 0x1E0
        PAD(96);
        ULONG worldDay;                             //0x240
        DWORD worldDaySetTick;                      //0x244
        // AoL, UoF
        Array<WorldKillCount, 2> killCount;         //0x248
        CRITICAL_SECTION cs;                        //0x350
        UINT32 guildHouseCount;                     //0x368
        UINT32 guildRankCount;                      //0x36C
        UINT32 guildHouseMaxCount;                  //0x370
        UINT32 guildRankMaxCount;                   //0x374
        UINT32 partyCount;                          //0x378
        UINT32 partyMaxCount;                       //0x37C
        UINT32 allCount;                            //0x380
        // 0x384

        static CUser* FindUser(ULONG id/*CUser->id*/);
        static CUser* FindUser(const char* charName/*eax*/);
        static int GetUserCount();
        static CZone* GetZone(int mapId/*eax*/);
        static ULONG GetWorldDay();
        static void SendAll(void* data/*ecx*/, int len/*eax*/);
        static void SendAllCountry(void* data/*ecx*/, int len/*eax*/, int byCountry);
        static void SetWorldDay(ULONG time/*eax*/);
    };
    #pragma pack(pop)

    // 0x587960
    static auto g_pWorld = (CWorld*)0x10A2018;
}
