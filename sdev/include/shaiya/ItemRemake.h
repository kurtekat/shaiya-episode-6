#pragma once
#include <algorithm>
#include <array>
#include <cstdint>
#include <ranges>
#include <vector>

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

    struct ItemRemakeContainsF
    {
        ItemRemakeContainsF(uint32_t itemId1, uint32_t itemId2, uint32_t itemId3)
            : m_itemId1(itemId1)
            , m_itemId2(itemId2)
            , m_itemId3(itemId3)
        {
        }

        bool operator()(const ItemRemake& itemRemake)
        {
            return std::ranges::contains(itemRemake.items, m_itemId1) &&
                   std::ranges::contains(itemRemake.items, m_itemId2) &&
                   std::ranges::contains(itemRemake.items, m_itemId3);
        }

    private:
        uint32_t m_itemId1;
        uint32_t m_itemId2;
        uint32_t m_itemId3;
    };

    inline std::vector<ItemRemake> g_itemRemake4{};
    inline std::vector<ItemRemake> g_itemRemake5{};
}
