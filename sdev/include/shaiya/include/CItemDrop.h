#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    static Address g_ItemDrop = 0x1091878;

    struct ItemInfo;

    #pragma pack(push, 1)
    struct CItemDrop
    {
        static ItemInfo* GetItem(int grade/*eax*/);
        static ItemInfo* GetItemPlz(int grade/*eax*/);
        static int GetItemCreateByGrade(int reqVg/*eax*/);
        static bool EnableItemCreateByGrade(int reqVg/*ecx*/);
    };
    #pragma pack(pop)
}
