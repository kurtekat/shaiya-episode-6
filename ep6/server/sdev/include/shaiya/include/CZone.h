#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    FWDDECL CMap;
    FWDDECL CMob;
    FWDDECL CNpc;
    FWDDECL CUser;
    FWDDECL SVector;

    #pragma pack(push, 1)
    struct CZone
    {
        PAD(24);
        ULONG id;   //0x18
        PAD(12);
        CMap* map;  //0x28
        //

        static CMob* FindMob(CZone* zone/*ecx*/, ULONG id/*CMob->id*/);
        static CNpc* FindNpc(CZone* zone/*ecx*/, ULONG id/*CNpc->id*/);
        static CUser* FindUser(CZone* zone/*ecx*/, ULONG id/*CUser->id*/);
        static int GetInsZonePortalCountry(CZone* zone/*esi*/, int id/*edx*/); 
        static bool MobGen(CZone* zone, int mobId/*ecx*/, int count/*eax*/, SVector* pos/*ebx*/);
        static bool MobRemove(CZone* zone, int mobId, int count, int cellX, int cellZ, SVector* pos);
        static bool MobRemoveById(CZone* zone/*ecx*/, ULONG id/*CMob->id*/);
        static void MoveMob(CMob* mob/*eax*/, float x, float y, float z, int motion);
        static void MoveNpc(CNpc* npc/*ebx*/, float x, float y, float z, int motion);
        static void NpcCreate(CZone* zone/*ecx*/, int npcType, int npcId, SVector* pos/*edi*/);
        static bool NpcRemove(CZone* zone, int npcType, int npcId, int count, int cellX/*eax*/, int cellZ/*ecx*/, SVector* pos);
        static void SendView(CZone* zone, void* data, int len, int cellX/*ecx*/, int cellZ/*eax*/);
        static void UpdateInsZonePortalCountry(CZone* zone/*esi*/, int id/*edi*/, int country/*ebx*/);
    };
    #pragma pack(pop)
}
