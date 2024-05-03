#include "include/shaiya/include/CWorldMgr.h"
using namespace shaiya;

CCharacter* CWorldMgr::FindUser(ULONG id/*CUser->id*/)
{
    typedef CCharacter* (__thiscall* LPFN)(void*, ULONG);
    return (*(LPFN)0x452B10)((void*)0x7C4A68, id);
}

CMonster* CWorldMgr::FindMob(ULONG id/*CMob->id*/)
{
    typedef CMonster* (__thiscall* LPFN)(void*, ULONG);
    return (*(LPFN)0x452B90)((void*)0x7C4A68, id);
}

CNpc* CWorldMgr::FindNpc(ULONG id/*CNpc->id*/)
{
    typedef CNpc* (__thiscall* LPFN)(void*, ULONG);
    return (*(LPFN)0x452C00)((void*)0x7C4A68, id);
}

void CWorldMgr::RenderEffect(int effectDataId, int effectSubId, D3DVECTOR* pos, D3DVECTOR* dir, D3DVECTOR* up, int unknown/*0:9*/)
{
    typedef void(__thiscall* LPFN)(void*, int, int, D3DVECTOR*, D3DVECTOR*, D3DVECTOR*, int);
    (*(LPFN)0x459120)((void*)0x7C4A68, effectDataId, effectSubId, pos, dir, up, unknown);
}
