#include "CPlayerData.h"
#include "GuildUserData.h"
using namespace shaiya;

int CPlayerData::GetItemRealType(int itemType)
{
    typedef int(__thiscall* LPFN)(void*, int);
    return (*(LPFN)0x4E5630)((void*)0x90D1D0, itemType);
}

GuildUserData* CPlayerData::GetGuildUserData(unsigned charId)
{
    typedef GuildUserData* (__thiscall* LPFN)(void*, unsigned);
    return (*(LPFN)0x4EB120)((void*)0x90D1D0, charId);
}
