#pragma once
#include <vector>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ItemRemake
    {
        int itemId1;
        int itemId2;
        int itemId3;
        int createType;
        int createTypeId;

        static void init();
    };
    #pragma pack(pop)

    inline std::vector<ItemRemake> g_itemRemake;
}
