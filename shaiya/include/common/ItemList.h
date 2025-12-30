#pragma once
#include <array>
#include <cstdint>

namespace shaiya
{
    constexpr int ItemListCount_EP5 = 8;
    constexpr int ItemListCount_EP6_4 = 17;

    #pragma pack(push, 1)
    template<size_t N>
    struct ItemList
    {
        std::array<uint8_t, N> type;
        std::array<uint8_t, N> typeId;
    };
    #pragma pack(pop)

    using ItemList_EP5 = ItemList<ItemListCount_EP5>;
    using ItemList_EP6 = ItemList<ItemListCount_EP5>;
    using ItemList_EP6_4 = ItemList<ItemListCount_EP6_4>;
}
