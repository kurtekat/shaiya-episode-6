#include <include/shaiya/include/CMob.h>
#include <include/shaiya/include/CNpc.h>
#include <include/shaiya/include/CZone.h>
#include <include/shaiya/include/SVector.h>
using namespace shaiya;

CMob* CZone::FindMob(CZone* zone/*ecx*/, ULONG id/*CMob->id*/)
{
    typedef CMob* (__thiscall* LPFN)(CZone*, ULONG);
    return (*(LPFN)0x41CFD0)(zone, id);
}

CNpc* CZone::FindNpc(CZone* zone/*ecx*/, ULONG id/*CNpc->id*/)
{
    typedef CNpc* (__thiscall* LPFN)(CZone*, ULONG);
    return (*(LPFN)0x41D4A0)(zone, id);
}

CUser* CZone::FindUser(CZone* zone/*ecx*/, ULONG id/*CUser->id*/)
{
    typedef CUser* (__thiscall* LPFN)(CZone*, ULONG);
    return (*(LPFN)0x41C6E0)(zone, id);
}

int CZone::GetCurUserCount(CZone* zone/*ecx*/)
{
    typedef int(__thiscall* LPFN)(CZone*);
    return (*(LPFN)0x429AF0)(zone);
}

int CZone::GetInsZonePortalCountry(CZone* zone/*esi*/, int id/*edx*/)
{
    Address u0x41DF50 = 0x41DF50;

    __asm
    {
        mov edx,id
        mov esi,zone
        call u0x41DF50
    }
}

bool CZone::MobGen(CZone* zone, int mobId/*ecx*/, int count/*eax*/, SVector* pos/*ebx*/)
{
    Address u0x4245A0 = 0x4245A0;

    __asm
    {
        mov ebx,pos
        mov eax,count
        mov ecx,mobId

        push zone
        call u0x4245A0
    }
}

bool CZone::MobRemove(CZone* zone, int mobId, int count, int cellX, int cellZ, SVector* pos)
{
    Address u0x424C30 = 0x424C30;

    __asm
    {
        mov ecx,cellZ
        mov edx,cellX

        push pos
        push count
        push mobId
        push zone
        call u0x424C30
    }
}

bool CZone::MobRemoveById(CZone* zone/*ecx*/, ULONG id/*CMob->id*/)
{
    typedef bool(__thiscall* LPFN)(CZone*, ULONG);
    return (*(LPFN)0x425430)(zone, id);
}

void CZone::MoveMob(CMob* mob/*eax*/, float x, float y, float z, int motion)
{
    Address u0x41D150 = 0x41D150;
    auto zone = mob->zone;

    __asm
    {
        sub esp,0xC

        push motion
        fld[z]
        fstp[esp+0x8]
        fld[y]
        fstp[esp+0x4]
        fld[x]
        fstp[esp]
        push zone

        mov eax, mob
        call u0x41D150
    }
}

void CZone::MoveNpc(CNpc* npc/*ebx*/, float x, float y, float z, int motion)
{
    typedef void(__stdcall* LPFN)(CMap*, float, float, float, int);
    __asm { mov ebx,npc }
    (*(LPFN)0x41D650)(npc->map, x, y, z, motion);
}

void CZone::NpcCreate(CZone* zone/*ecx*/, int npcType, int npcId, SVector* pos/*edi*/)
{
    pos->y -= 0.9f;

    typedef void(__thiscall* LPFN)(CZone*, int, int);
    __asm { mov edi,pos }
    (*(LPFN)0x4255D0)(zone, npcType, npcId);
}

bool CZone::NpcRemove(CZone* zone, int npcType, int npcId, int count, int cellX/*eax*/, int cellZ/*ecx*/, SVector* pos)
{
    Address u0x4257A0 = 0x4257A0;

    __asm
    {
        mov eax,cellZ
        mov ecx,cellX

        push pos
        push count
        push npcId
        push npcType
        push zone
        call u0x4257A0
    }
}

void CZone::PSendView(CZone* zone, void* data, int len, SVector* base, float radius, ULONG senderId, ULONG targetId, int priority)
{
    typedef void(__stdcall* LPFN)(CZone*, void*, int, SVector*, float, ULONG, ULONG, int);
    (*(LPFN)0x427CF0)(zone, data, len, base, radius, senderId, targetId, priority);
}

void CZone::SendView(CZone* zone, void* data, int len, int cellX/*ecx*/, int cellZ/*eax*/)
{
    Address u0x427470 = 0x427470;

    __asm
    {
        mov eax,cellZ
        mov ecx,cellX

        push len
        push data
        push zone
        call u0x427470
    }
}

void CZone::UpdateInsZonePortalCountry(CZone* zone/*esi*/, int id/*edi*/, int country/*ebx*/)
{
    Address u0x41DF80 = 0x41DF80;

    __asm
    {
        mov ebx,country
        mov edi,id
        mov esi,zone
        call u0x41DF80
    }
}
