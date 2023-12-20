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

void CMob::UseSkill(CMob* mob/*edi*/, DWORD time, CUser* user/*edx*/, CGameData::SkillInfo* info/*eax*/)
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

void CMob::SetAttack(CMob* mob/*esi*/)
{
    Address u0x4A0DB0 = 0x4A0DB0;

    __asm
    {
        mov esi,mob
        call u0x4A0DB0
    }
}

void CMob::SetSkillAbility(CMob* mob/*edx*/, int _type/*ecx*/, int value/*eax*/)
{
    Address u0x4B5A70 = 0x4B5A70;

    __asm
    {
        mov eax,value
        mov ecx,_type
        mov edx,mob
        call u0x4B5A70
    }
}

void CMob::SetStatus(CMob* mob/*eax*/, int status/*ecx*/)
{
    Address u0x4A12C0 = 0x4A12C0;

    __asm
    {
        mov ecx,status
        mov eax,mob
        call u0x4A12C0
    }
}
