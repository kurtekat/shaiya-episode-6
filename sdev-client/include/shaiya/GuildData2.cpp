#include "GuildData2.h"
using namespace shaiya;

GuildData2* GuildData2::Find(unsigned guildId)
{
    typedef GuildData2* (__thiscall* LPFN)(void*, unsigned);
    return (*(LPFN)0x4446E0)((void*)0x22AF6DC, guildId);
}
