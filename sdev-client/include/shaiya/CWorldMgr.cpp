#include "CWorldMgr.h"
using namespace shaiya;

CCharacter* CWorldMgr::FindUser(uint_t objectId)
{
    typedef CCharacter* (__thiscall* LPFN)(void*, uint_t);
    return (*(LPFN)0x452B10)((void*)0x7C4A68, objectId);
}

CMonster* CWorldMgr::FindMob(uint_t objectId)
{
    typedef CMonster* (__thiscall* LPFN)(void*, uint_t);
    return (*(LPFN)0x452B90)((void*)0x7C4A68, objectId);
}

CNpc* CWorldMgr::FindNpc(uint_t objectId)
{
    typedef CNpc* (__thiscall* LPFN)(void*, uint_t);
    return (*(LPFN)0x452C00)((void*)0x7C4A68, objectId);
}

void CWorldMgr::RenderEffect(uint_t effectDataId, uint_t effectSubId, D3DVECTOR* pos, D3DVECTOR* dir, D3DVECTOR* up, int unknown/*0:9*/)
{
    typedef void(__thiscall* LPFN)(void*, uint_t, uint_t, D3DVECTOR*, D3DVECTOR*, D3DVECTOR*, int);
    (*(LPFN)0x459120)((void*)0x7C4A68, effectDataId, effectSubId, pos, dir, up, unknown);
}
