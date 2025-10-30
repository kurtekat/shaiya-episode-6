#include "CItem.h"
using namespace shaiya;

char CItem::GetEnchantStep(CItem* item/*edx*/)
{
    unsigned u0x4D2920 = 0x4D2920;

    __asm
    {
        mov edx,item
        call u0x4D2920
    }
}

int CItem::GetGemCount(CItem* item/*ecx*/)
{
    typedef int(__thiscall* LPFN)(CItem*);
    return (*(LPFN)0x4D2260)(item);
}

int CItem::GetGemSlot(CItem* item/*ecx*/)
{
    typedef int(__thiscall* LPFN)(CItem*);
    return (*(LPFN)0x4D2240)(item);
}

void CItem::InitCraftExpansion(CItem* item/*eax*/)
{
    unsigned u0x4D2470 = 0x4D2470;

    __asm
    {
        mov eax,item
        call u0x4D2470
    }
}

bool CItem::IsAccessory(CItem* item/*eax*/)
{
    unsigned u0x4D2110 = 0x4D2110;

    __asm
    {
        mov eax,item
        call u0x4D2110
    }
}

bool CItem::IsEquipment(CItem* item/*eax*/)
{
    unsigned u0x405960 = 0x405960;

    __asm
    {
        mov eax,item
        call u0x405960
    }
}

bool CItem::IsEquipSex(CItem* item/*eax*/, int sex/*ecx*/)
{
    unsigned u0x468180 = 0x468180;

    __asm
    {
        mov eax,item
        mov ecx,sex
        call u0x468180
    }
}

bool CItem::IsEtin(CItem* item/*eax*/)
{
    unsigned u0x484D80 = 0x484D80;

    __asm
    {
        mov eax,item
        call u0x484D80
    }
}

bool CItem::IsQuest(CItem* item/*eax*/)
{
    unsigned u0x41BA50 = 0x41BA50;

    __asm
    {
        mov eax,item
        call u0x41BA50
    }
}

bool CItem::IsOneHandWeapon(CItem* item/*eax*/)
{
    unsigned u0x468120 = 0x468120;

    __asm
    {
        mov eax,item
        call u0x468120
    }
}

bool CItem::IsShield(CItem* item/*eax*/)
{
    unsigned u0x468150 = 0x468150;

    __asm
    {
        mov eax,item
        call u0x468150
    }
}

bool CItem::IsWeapon(CItem* item/*eax*/)
{
    unsigned u0x468100 = 0x468100;

    __asm
    {
        mov eax,item
        call u0x468100
    }
}

void CItem::ReGenerationCraftExpansion(CItem* item/*esi*/, bool compose)
{
    unsigned u0x4D29C0 = 0x4D29C0;

    __asm
    {
        movzx eax,compose
        push eax
        mov esi,item
        call u0x4D29C0
    }
}
