#pragma once
#include <shaiya/include/common.h>
#include "include/shaiya/include/CMap.h"
#include "include/shaiya/include/SSyncList.h"
#include "include/shaiya/include/SSyncMap.h"

namespace shaiya
{
    struct CItem;
    struct CMapRegion;
    struct CMob;
    struct CNpc;
    struct CTrap;
    struct CUser;
    struct SVector;

    #pragma pack(push, 1)
    struct CZone
    {
        PAD(24);
        ULONG id;                       //0x18
        PAD(12);
        CMap* map;                      //0x28
        PAD(12);
        SSyncList<int> list38;          //0x38
        SSyncMap<ULONG, CUser*> users;  //0x64
        SSyncMap<ULONG, CMob*> mobs;    //0xAC
        SSyncMap<ULONG, CNpc*> npcs;    //0xF4
        SSyncMap<ULONG, CItem*> items;  //0x13C
        SSyncList<CUser> userList;      //0x184
        SSyncList<CMob> mobList;        //0x1B0
        SSyncList<CNpc> npcList;        //0x1DC
        SSyncList<CItem> itemList;      //0x208
        SSyncList<CTrap> trapList;      //0x234
        SSyncList<int> list260;         //0x260
        PAD(80);
        UINT32 mobAreaCount;            //0x2DC
        MapMob* mobAreas;               //0x2E0
        UINT32 bossMobCount;            //0x2E4
        MapBoss* bossMobs;              //0x2E8
        MapWeather weather;             //0x2EC
        PAD(8);
        UINT32 regionCount;             //0x310
        CMapRegion* regions;            //0x314
        // 0x318

        static CMob* FindMob(CZone* zone/*ecx*/, ULONG objectId);
        static CNpc* FindNpc(CZone* zone/*ecx*/, ULONG objectId);
        static CUser* FindUser(CZone* zone/*ecx*/, ULONG objectId);
        static MapBoss* GetBossMobInfo(CZone* zone/*ecx*/, int index/*eax*/);
        static int GetCurUserCount(CZone* zone/*ecx*/);
        static int GetInsZonePortalCountry(CZone* zone/*esi*/, int insZoneId/*edx*/);
        static bool MobGen(CZone* zone, int mobId/*ecx*/, int count/*eax*/, SVector* pos/*ebx*/);
        static ULONG MobGenEx(CZone* zone, ULONG objectId, int mobId/*ecx*/, int count/*eax*/, SVector* pos/*ebx*/);
        static bool MobRemove(CZone* zone, int mobId, int count, int cellX, int cellZ, SVector* pos);
        static bool MobRemoveById(CZone* zone/*ecx*/, ULONG objectId);
        static void MoveAllBindPos(CZone* zone/*edi*/);
        static bool MoveUser(CZone* zone, CUser* user/*edi*/, float x, float y, float z);
        static bool NpcCreate(CZone* zone/*ecx*/, int npcType, int npcTypeId, SVector* pos/*edi*/);
        static bool NpcRemove(CZone* zone, int npcType, int npcTypeId, int count, int cellX/*eax*/, int cellZ/*ecx*/, SVector* pos);
        static void PSendView(CZone* zone, void* packet, int length, SVector* base, float radius, ULONG senderId, ULONG targetId, int priority);
        static void SendView(CZone* zone, void* packet, int length, int cellX/*ecx*/, int cellZ/*eax*/);
        static void UpdateInsZonePortalCountry(CZone* zone/*esi*/, int id/*edi*/, int country/*ebx*/);
    };
    #pragma pack(pop)

    static_assert(sizeof(CZone) == 0x318);
}
