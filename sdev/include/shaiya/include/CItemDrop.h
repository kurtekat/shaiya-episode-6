#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/CGameData.h>

namespace shaiya
{
    static Address g_ItemDrop = 0x1091878;

    #pragma pack(push, 1)
    struct CItemDrop
    {
        static CGameData::ItemInfo* GetItem(int grade/*eax*/);
        static CGameData::ItemInfo* GetItemPlz(int grade/*eax*/);
    };
    #pragma pack(pop)
}
