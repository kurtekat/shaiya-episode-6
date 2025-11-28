#pragma once
#include <shaiya/include/common.h>
#include "CZoneLink.h"
#include "InsZonePortal.h"
#include "MapWeather.h"
#include "SNode.h"
#include "SSyncList.h"
#include "SSyncMap.h"

namespace shaiya
{
    struct CCell;
    struct CDoor;
    struct CItem;
    struct CMap;
    struct CMapRegion;
    struct CMob;
    struct CNpc;
    struct CObjectLink;
    struct CTrap;
    struct CUser;
    struct CZoneNode;
    struct MapBoss;
    struct MapMob;
    struct SNodeSendAll;
    struct SVector;

    #pragma pack(push, 1)
    struct CZone : SNode
    {
        CZoneLink link;                        //0x08
        CZoneNode* node;                       //0x14
        int32_t id;                            //0x18
        PAD(12);
        CMap* map;                             //0x28
        int32_t cellXCount;                    //0x2C
        int32_t cellZCount;                    //0x30
        CCell** cell;
        SSyncList<CUser> waitList;             //0x38
        SSyncMap<uint32_t, CUser*> userMap;    //0x64
        SSyncMap<uint32_t, CMob*> mobMap;      //0xAC
        SSyncMap<uint32_t, CNpc*> npcMap;      //0xF4
        SSyncMap<uint32_t, CItem*> itemMap;    //0x13C
        SSyncList<CObjectLink> userList;       //0x184
        SSyncList<CObjectLink> mobList;        //0x1B0
        SSyncList<CObjectLink> npcList;        //0x1DC
        SSyncList<CObjectLink> itemList;       //0x208
        SSyncList<CTrap> trapList;             //0x234
        SSyncList<SNodeSendAll> sendAllQueue;  //0x260
        Array<InsZonePortal, 10> portals;      //0x28C
        int32_t mapMobCount;                   //0x2DC
        MapMob* mapMobs;                       //0x2E0
        int32_t mapBossCount;                  //0x2E4
        MapBoss* mapBosses;                    //0x2E8
        MapWeather mapWeather;                 //0x2EC
        int32_t doorCount;                     //0x308
        CDoor* doors;                          //0x30C
        int32_t mapRegionCount;                //0x310
        CMapRegion* mapRegions;                //0x314
        // 0x318

        static CMob* FindMob(CZone* zone/*ecx*/, unsigned objectId);
        static CNpc* FindNpc(CZone* zone/*ecx*/, unsigned objectId);
        static CUser* FindUser(CZone* zone/*ecx*/, unsigned objectId);
        static bool MobGen(CZone* zone, int mobId/*ecx*/, int count/*eax*/, SVector* pos/*ebx*/);
        static unsigned MobGenEx(CZone* zone, unsigned objectId, int mobId/*ecx*/, int count/*eax*/, SVector* pos/*ebx*/);
        static bool MobRemove(CZone* zone, int mobId, int count, int cellX, int cellZ, SVector* pos);
        static bool MobRemoveById(CZone* zone/*ecx*/, unsigned objectId);
        static void MoveAllBindPos(CZone* zone/*edi*/);
        static bool MoveUser(CZone* zone, CUser* user/*edi*/, float x, float y, float z);
        static bool NpcCreate(CZone* zone/*ecx*/, int npcType, int npcTypeId, SVector* pos/*edi*/);
        static bool NpcRemove(CZone* zone, int npcType, int npcTypeId, int count, int cellX/*eax*/, int cellZ/*ecx*/, SVector* pos);
        static void PSendView(CZone* zone, void* packet, int length, SVector* base, float radius, unsigned senderId, unsigned targetId, int priority);
        static void SendView(CZone* zone, void* packet, int length, int cellX/*ecx*/, int cellZ/*eax*/);
    };
    #pragma pack(pop)

    static_assert(sizeof(CZone) == 0x318);
}
