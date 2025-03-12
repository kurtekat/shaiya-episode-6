#include "include/shaiya/include/CMap.h"
#include "include/shaiya/include/CMob.h"
#include "include/shaiya/include/CNpc.h"
#include "include/shaiya/include/CZone.h"
#include "include/shaiya/include/Obelisk.h"
#include "include/shaiya/include/SVector.h"
using namespace shaiya;

CMob* CZone::FindMob(CZone* zone/*ecx*/, ULONG objectId)
{
    typedef CMob* (__thiscall* LPFN)(CZone*, ULONG);
    return (*(LPFN)0x41CFD0)(zone, objectId);
}

CNpc* CZone::FindNpc(CZone* zone/*ecx*/, ULONG objectId)
{
    typedef CNpc* (__thiscall* LPFN)(CZone*, ULONG);
    return (*(LPFN)0x41D4A0)(zone, objectId);
}

CUser* CZone::FindUser(CZone* zone/*ecx*/, ULONG objectId)
{
    typedef CUser* (__thiscall* LPFN)(CZone*, ULONG);
    return (*(LPFN)0x41C6E0)(zone, objectId);
}

MapBoss* CZone::GetBossMobInfo(CZone* zone/*ecx*/, int index/*eax*/)
{
    unsigned u0x4224C0 = 0x4224C0;

    __asm
    {
        mov eax,index
        mov ecx,zone
        call u0x4224C0
    }
}

int CZone::GetCurUserCount(CZone* zone/*ecx*/)
{
    typedef int(__thiscall* LPFN)(CZone*);
    return (*(LPFN)0x429AF0)(zone);
}

int CZone::GetInsZonePortalCountry(CZone* zone/*esi*/, int insZoneId/*edx*/)
{
    unsigned u0x41DF50 = 0x41DF50;

    __asm
    {
        mov edx,insZoneId
        mov esi,zone
        call u0x41DF50
    }
}

bool CZone::MobGen(CZone* zone, int mobId/*ecx*/, int count/*eax*/, SVector* pos/*ebx*/)
{
    unsigned u0x4245A0 = 0x4245A0;

    __asm
    {
        mov ebx,pos
        mov eax,count
        mov ecx,mobId

        push zone
        call u0x4245A0
    }
}

ULONG CZone::MobGenEx(CZone* zone, ULONG objectId, int mobId/*ecx*/, int count/*eax*/, SVector* pos/*ebx*/)
{
    unsigned u0x424750 = 0x424750;

    __asm
    {
        mov ebx,pos
        mov eax,count
        mov ecx,mobId
        
        push objectId
        push zone
        call u0x424750
    }
}

bool CZone::MobRemove(CZone* zone, int mobId, int count, int cellX, int cellZ, SVector* pos)
{
    unsigned u0x424C30 = 0x424C30;

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

bool CZone::MobRemoveById(CZone* zone/*ecx*/, ULONG objectId)
{
    typedef bool(__thiscall* LPFN)(CZone*, ULONG);
    return (*(LPFN)0x425430)(zone, objectId);
}

void CZone::MoveAllBindPos(CZone* zone/*edi*/)
{
    unsigned u0x429A00 = 0x429A00;

    _asm
    {
        mov edi,zone
        call u0x429A00
    }
}

bool CZone::MoveUser(CZone* zone, CUser* user/*edi*/, float x, float y, float z)
{
    unsigned u0x41CA80 = 0x41CA80;

    __asm
    {
        sub esp,0xC
        fld [z]
        fstp [esp+0x8]
        fld [y]
        fstp [esp+0x4]
        fld [x]
        fstp [esp]
        push zone
        mov edi,user
        call u0x41CA80
    }
}

bool CZone::NpcCreate(CZone* zone/*ecx*/, int npcType, int npcTypeId, SVector* pos/*edi*/)
{
    pos->y -= 0.9f;

    unsigned u0x4255D0 = 0x4255D0;

    __asm
    {
        push npcTypeId
        push npcType
        mov edi,pos
        mov ecx,zone
        call u0x4255D0
    }
}

bool CZone::NpcRemove(CZone* zone, int npcType, int npcTypeId, int count, int cellX/*eax*/, int cellZ/*ecx*/, SVector* pos)
{
    unsigned u0x4257A0 = 0x4257A0;

    __asm
    {
        mov eax,cellZ
        mov ecx,cellX

        push pos
        push count
        push npcTypeId
        push npcType
        push zone
        call u0x4257A0
    }
}

void CZone::PSendView(CZone* zone, void* packet, int length, SVector* base, float radius, ULONG senderId, ULONG targetId, int priority)
{
    typedef void(__stdcall* LPFN)(CZone*, void*, int, SVector*, float, ULONG, ULONG, int);
    (*(LPFN)0x427CF0)(zone, packet, length, base, radius, senderId, targetId, priority);
}

void CZone::SendView(CZone* zone, void* packet, int _length, int cellX/*ecx*/, int cellZ/*eax*/)
{
    unsigned u0x427470 = 0x427470;

    __asm
    {
        mov eax,cellZ
        mov ecx,cellX

        push _length
        push packet
        push zone
        call u0x427470
    }
}

void CZone::UpdateInsZonePortalCountry(CZone* zone/*esi*/, int insZoneId/*edi*/, int country/*ebx*/)
{
    unsigned u0x41DF80 = 0x41DF80;

    __asm
    {
        mov ebx,country
        mov edi,insZoneId
        mov esi,zone
        call u0x41DF80
    }
}
