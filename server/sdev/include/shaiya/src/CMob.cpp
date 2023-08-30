#include <include/shaiya/include/CMob.h>
using namespace shaiya;

int CMob::GetCountry(CMob* mob/*eax*/)
{
    Address u0x457CE0 = 0x457CE0;

    __asm
    {
        mov eax,mob
        call u0x457CE0
    }
}

void CMob::UseSkill(CMob* mob/*edi*/, TickCount time, CUser* user/*edx*/, CGameData::SkillInfo* info/*eax*/)
{
    Address u0x4B9280 = 0x4B9280;

    __asm
    {
        push time
        mov eax,info
        mov edx,user
        mov edi,mob
        call u0x4B9280
    }
}

bool CMob::EnableApplyRangeItem(CUser* base/*eax*/, CUser* user/*ecx*/)
{
    Address u0x4BAED0 = 0x4BAED0;

    __asm
    {
        mov eax,base
        mov ecx,user
        call u0x4BAED0
    }
}
