#pragma once
#include <array>
#include <cstdint>
#include <vector>

namespace shaiya
{
    using ItemId = uint32_t;

    #pragma pack(push, 1)
    struct ItemRemake
    {
        std::array<ItemId, 3> items;
        int32_t newItemType;
        int32_t newItemTypeId;
    };
    #pragma pack(pop)

    inline std::vector<ItemRemake> g_itemRemake4{};
    inline std::vector<ItemRemake> g_itemRemake5{};
}
