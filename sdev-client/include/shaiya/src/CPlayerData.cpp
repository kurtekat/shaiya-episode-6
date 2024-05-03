#include "include/shaiya/include/CPlayerData.h"
#include "include/shaiya/include/GuildUserData.h"
using namespace shaiya;

GuildUserData* CPlayerData::GetGuildUserData(ULONG charId)
{
    typedef GuildUserData* (__thiscall* LPFN)(void*, ULONG);
    return (*(LPFN)0x4EB120)((void*)0x90D1D0, charId);
}
