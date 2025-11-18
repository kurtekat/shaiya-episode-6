#pragma once
#include <array>
#include <map>
#include <vector>
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ItemSynthesis
    {
        int32_t successRate;
        Array<uint8_t, 24> materialType;
        Array<uint8_t, 24> materialTypeId;
        Array<uint8_t, 24> materialCount;
        int32_t newItemType;
        int32_t newItemTypeId;
        int32_t newItemCount;

        static constexpr uint32_t minMoney = 100'000'000;
        static constexpr uint32_t maxMoney = minMoney * 5;
        static constexpr int minSuccessRate = 100;
        static constexpr int maxSuccessRate = 10000;
    };
    #pragma pack(pop)

    static_assert(ItemSynthesis::minMoney != 0);
    inline std::map<uint32_t, std::vector<ItemSynthesis>> g_itemSynthesis{};
}
