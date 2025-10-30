#include "CWorldMgr.h"
using namespace shaiya;

CCharacter* CWorldMgr::FindUser(uint objectId)
{
    typedef CCharacter* (__thiscall* LPFN)(void*, uint);
    return (*(LPFN)0x452B10)((void*)0x7C4A68, objectId);
}

CMonster* CWorldMgr::FindMob(uint objectId)
{
    typedef CMonster* (__thiscall* LPFN)(void*, uint);
    return (*(LPFN)0x452B90)((void*)0x7C4A68, objectId);
}

CNpc* CWorldMgr::FindNpc(uint objectId)
{
    typedef CNpc* (__thiscall* LPFN)(void*, uint);
    return (*(LPFN)0x452C00)((void*)0x7C4A68, objectId);
}

void CWorldMgr::RenderEffect(uint effectDataId, uint effectSubId, D3DVECTOR* pos, D3DVECTOR* dir, D3DVECTOR* up, int unknown/*0:9*/)
{
    typedef void(__thiscall* LPFN)(void*, uint, uint, D3DVECTOR*, D3DVECTOR*, D3DVECTOR*, int);
    (*(LPFN)0x459120)((void*)0x7C4A68, effectDataId, effectSubId, pos, dir, up, unknown);
}
