#pragma once
#include <map>
#include <vector>
#include <shaiya/include/common.h>

namespace shaiya
{
    namespace ItemSynthesisConstants
    {
        // Zero, or a value evenly divisible by 100
        inline constexpr unsigned goldPerPercentage = 100'000'000;
        static_assert(goldPerPercentage % 100 == 0);

        inline constexpr unsigned minMoney = goldPerPercentage / 100;
        inline constexpr unsigned maxMoney = goldPerPercentage * 5;
        inline constexpr int minSuccessRate = 100;
        inline constexpr int maxSuccessRate = 10000;
    };

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
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChaoticSquare
    {
        uint32_t itemId;
        Array<uint8_t, 10> newItemType;
        Array<uint8_t, 10> newItemTypeId;
    };
    #pragma pack(pop)

    inline std::map<uint32_t, std::vector<ItemSynthesis>> g_itemSyntheses{};
    inline std::vector<ChaoticSquare> g_chaoticSquares{};
}
