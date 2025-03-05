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
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemRemake4
    {
        static void init();
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemRemake5
    {
        static void init();
    };
    #pragma pack(pop)

    inline std::vector<ItemRemake> g_itemRemake4;
    inline std::vector<ItemRemake> g_itemRemake5;
}
