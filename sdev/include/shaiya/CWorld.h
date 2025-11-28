#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common.h>
#include "KillCountInfo.h"
#include "SSyncList.h"
#include "SSyncMap.h"

namespace shaiya
{
    struct CDead;
    struct CMap;
    struct CUser;
    struct CZone;
    struct CZoneNode;
    struct SNodeSendAll;

    #pragma pack(push, 1)
    struct CWorld
    {
        uint32_t allocZoneIdCount;                 //0x00
        CZoneNode* zoneList;                       //0x04
        int32_t mapCount;                          //0x08
        CMap* maps;                                //0x0C
        SSyncMap<uint32_t, CUser*> userMap;        //0x10
        SSyncMap<String<32>, CUser*> charNameMap;  //0x58
        SSyncMap<uint32_t, CUser*> billMap;        //0xA0
        SSyncMap<String<32>, CUser*> billNameMap;  //0xE8
        SSyncList<CUser> connectedList;            //0x130
        SSyncList<CUser> selectedServerList;       //0x15C
        SSyncList<CUser> waitList;                 //0x188
        SSyncMap<uint32_t, CDead> deadMap;         //0x1B4
        CRITICAL_SECTION cs;                       //0x1FC
        SSyncList<SNodeSendAll> sendAllQueue;      //0x214
        time32_t startWorldTime;                   //0x240
        tick32_t startWorldTick;                   //0x244
        // AoL, UoF
        Array<KillCountInfo, 2> kcInfo;            //0x248
        CRITICAL_SECTION kc;                       //0x350
        uint32_t guildHouseZoneCount;              //0x368
        uint32_t guildRankZoneCount;               //0x36C
        uint32_t guildHouseZoneMaxCount;           //0x370
        uint32_t guildRankZoneMaxCount;            //0x374
        uint32_t partyZoneCount;                   //0x378
        uint32_t partyZoneMaxCount;                //0x37C
        uint32_t instanceZoneCount;                //0x380
        // 0x384

        static CUser* FindUser(unsigned objectId);
        static CUser* FindUser(const char* charName/*eax*/);
        static CUser* FindUserBill(unsigned billingId);
        static CZone* GetZone(int mapId/*eax*/);
        static void SendAll(void* packet/*ecx*/, int length/*eax*/);
        static void SendAllCountry(void* packet/*ecx*/, int length/*eax*/, int country);
        static void ZoneLeaveUserMove(CUser* user/*edi*/, int mapId, float x, float y, float z);
    };
    #pragma pack(pop)

    static_assert(sizeof(CWorld) == 0x384);
    static auto g_pWorld = (CWorld*)0x10A2018; // 0x587960
}
