#include <include/shaiya/include/CGameData.h>
using namespace shaiya;

CGameData::ItemInfo* CGameData::GetItemInfo(int _type/*eax*/, int typeId/*ecx*/)
{
    Address u0x4059B0 = 0x4059B0;

    __asm
    {
        mov ecx,typeId
        mov eax,_type
        call u0x4059B0
    }
}

CGameData::MobInfo* CGameData::GetMobInfo(int mobId/*eax*/)
{
    Address u0x408C00 = 0x408C00;

    __asm
    {
        mov ecx,g_GameData
        mov eax,mobId
        call u0x408C00
    }
}

CGameData::KillCountStatus* CGameData::GetKCStatusByCount(int country/*eax*/, ULONG killCount/*ebx*/)
{
    Address u0x418FC0 = 0x418FC0;

    __asm
    {
        mov eax,country
        mov ebx,killCount
        call u0x418FC0
    }
}

int CGameData::GetKCStatusMax(int country/*eax*/)
{
    Address u0x419020 = 0x419020;

    __asm
    {
        mov eax,country
        call u0x419020
    }
}

int CGameData::GetKCStatusMaxKillCount(int country/*eax*/)
{
    Address u0x4033E0 = 0x4033E0;

    __asm
    {
        mov eax,country
        call u0x4033E0
    }
}

CGameData::ProductInfo* CGameData::GetProductInfo(const char* productCode/*eax*/)
{
    Address u0x47A5F0 = 0x47A5F0;

    __asm
    {
        mov eax,[productCode]
        call u0x47A5F0
    }
}

CGameData::SkillInfo* CGameData::GetSkillInfo(int skillId/*eax*/, int skillLv/*edx*/)
{
    Address u0x41BB30 = 0x41BB30;

    __asm
    {
        mov edx,skillLv
        mov eax,skillId
        call u0x41BB30
    }
}
