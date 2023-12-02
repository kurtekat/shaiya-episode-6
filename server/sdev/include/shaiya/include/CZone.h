#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/SSyncList.h>
#include <include/shaiya/include/SSyncMap.h>

namespace shaiya
{
    struct CItem;
    struct CMap;
    struct CMob;
    struct CNpc;
    struct CTrap;
    struct CUser;
    struct SVector;

    #pragma pack(push, 1)
    struct CZone
    {
        PAD(24);
        ULONG id;                         //0x18
        PAD(12);
        CMap* map;                        //0x28
        PAD(12);
        SSyncList<void> list38;           //0x38
        SSyncMap<ULONG, CUser*> userMap;  //0x64
        SSyncMap<ULONG, CMob*> mobMap;    //0xAC
        SSyncMap<ULONG, CNpc*> npcMap;    //0xF4
        SSyncMap<ULONG, CItem*> itemMap;  //0x13C
        SSyncList<CUser> userList;        //0x184
        SSyncList<CMob> mobList;          //0x1B0
        SSyncList<CNpc> npcList;          //0x1DC
        SSyncList<CItem> itemList;        //0x208
        SSyncList<CTrap> trapList;        //0x234
        SSyncList<void> list260;          //0x260
        // 0x2A4
        PAD(116);
        // 0x318

        static CMob* FindMob(CZone* zone/*ecx*/, ULONG id/*CMob->id*/);
        static CNpc* FindNpc(CZone* zone/*ecx*/, ULONG id/*CNpc->id*/);
        static CUser* FindUser(CZone* zone/*ecx*/, ULONG id/*CUser->id*/);
        static int GetCurUserCount(CZone* zone/*ecx*/);
        static int GetInsZonePortalCountry(CZone* zone/*esi*/, int id/*edx*/); 
        static bool MobGen(CZone* zone, int mobId/*ecx*/, int count/*eax*/, SVector* pos/*ebx*/);
        static bool MobRemove(CZone* zone, int mobId, int count, int cellX, int cellZ, SVector* pos);
        static bool MobRemoveById(CZone* zone/*ecx*/, ULONG id/*CMob->id*/);
        static void MoveMob(CMob* mob/*eax*/, float x, float y, float z, int motion);
        static void MoveNpc(CNpc* npc/*ebx*/, float x, float y, float z, int motion);
        static void NpcCreate(CZone* zone/*ecx*/, int npcType, int npcId, SVector* pos/*edi*/);
        static bool NpcRemove(CZone* zone, int npcType, int npcId, int count, int cellX/*eax*/, int cellZ/*ecx*/, SVector* pos);
        static void PSendView(CZone* zone, void* data, int len, SVector* base, float radius, ULONG senderId, ULONG targetId, int priority);
        static void SendView(CZone* zone, void* data, int len, int cellX/*ecx*/, int cellZ/*eax*/);
        static void UpdateInsZonePortalCountry(CZone* zone/*esi*/, int id/*edi*/, int country/*ebx*/);
    };
    #pragma pack(pop)
}
