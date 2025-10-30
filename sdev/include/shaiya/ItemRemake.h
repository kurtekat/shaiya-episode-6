#pragma once
#include <array>
#include <vector>
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ItemRemake
    {
        std::array<uint32_t, 3> items;
        int32_t newItemType;
        int32_t newItemTypeId;
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
