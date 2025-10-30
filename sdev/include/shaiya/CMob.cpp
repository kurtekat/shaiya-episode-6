#include "CMob.h"
#include "SkillInfo.h"
using namespace shaiya;

bool CMob::IsBossMob(CMob* mob/*eax*/)
{
    unsigned u0x4585F0 = 0x4585F0;

    __asm
    {
        mov eax,mob
        call u0x4585F0
    }
}

bool CMob::IsObelisk(CMob* mob/*eax*/)
{
    unsigned u0x45A130 = 0x45A130;

    __asm
    {
        mov eax,mob
        call u0x45A130
    }
}
