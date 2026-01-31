#pragma once
#include <array>
#include <cstdint>

namespace shaiya
{
    #pragma pack(push, 1)
    template<size_t N>
    struct ItemList
    {
        std::array<uint8_t, N> type;
        std::array<uint8_t, N> typeId;
    };
    #pragma pack(pop)

    using ItemList_EP5 = ItemList<8>;
    using ItemList_EP6 = ItemList<8>;
    using ItemList_EP6_4 = ItemList<17>;
}
