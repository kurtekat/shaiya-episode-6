#include "include/shaiya/include/CItemDrop.h"
#include "include/shaiya/include/ItemInfo.h"
using namespace shaiya;

ItemInfo* CItemDrop::GetItem(int grade/*eax*/)
{
    Address u0x4D5E90 = 0x4D5E90;

    __asm
    {
        mov eax,grade
        mov ecx,g_ItemDrop
        call u0x4D5E90
    }
}

ItemInfo* CItemDrop::GetItemPlz(int grade/*eax*/)
{
    Address u0x4D5F30 = 0x4D5F30;

    __asm
    {
        mov eax,grade
        mov edi,g_ItemDrop
        call u0x4D5F30
    }
}

int CItemDrop::GetItemCreateByGrade(int reqVg/*eax*/)
{
    Address u0x4D7620 = 0x4D7620;

    __asm
    {
        mov edi,reqVg
        movsx eax,di
        mov ecx,g_ItemDrop
        call u0x4D7620
    }
}

bool CItemDrop::EnableItemCreateByGrade(int reqVg/*ecx*/)
{
    Address u0x4D7690 = 0x4D7690;

    __asm
    {
        mov edi,reqVg
        movsx ecx,di
        mov esi,g_ItemDrop
        call u0x4D7690
    }
}
