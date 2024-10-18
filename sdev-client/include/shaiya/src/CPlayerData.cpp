#include "include/shaiya/include/CPlayerData.h"
#include "include/shaiya/include/GuildUserData.h"
using namespace shaiya;

UINT8 CPlayerData::GetItemRealType(int itemType)
{
    typedef UINT8(__thiscall* LPFN)(void*, int);
    return (*(LPFN)0x4E5630)((void*)0x90D1D0, itemType);
}

GuildUserData* CPlayerData::GetGuildUserData(ULONG charId)
{
    typedef GuildUserData* (__thiscall* LPFN)(void*, ULONG);
    return (*(LPFN)0x4EB120)((void*)0x90D1D0, charId);
}
