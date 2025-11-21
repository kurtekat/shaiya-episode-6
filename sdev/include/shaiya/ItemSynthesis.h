#pragma once
#include <array>
#include <cstdint>
#include <map>
#include <vector>

namespace shaiya
{
    struct ItemSynthesisConstants
    {
        // Zero, or a value evenly divisible by 100
        static constexpr uint32_t GoldPerPercentage = 100'000'000;
        static_assert(GoldPerPercentage % 100 == 0);
        static constexpr uint32_t MinMoney = GoldPerPercentage / 100;
        static constexpr uint32_t MaxMoney = GoldPerPercentage * 5;

        static constexpr int MinSuccessRate = 100;
        static constexpr int MaxSuccessRate = 10000;
    };

    #pragma pack(push, 1)
    struct ItemSynthesis
    {
        int32_t successRate;
        std::array<uint8_t, 24> materialType;
        std::array<uint8_t, 24> materialTypeId;
        std::array<uint8_t, 24> materialCount;
        int32_t newItemType;
        int32_t newItemTypeId;
        int32_t newItemCount;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChaoticSquare
    {
        uint32_t itemId;
        std::array<uint8_t, 10> newItemType;
        std::array<uint8_t, 10> newItemTypeId;
    };
    #pragma pack(pop)

    inline std::map<uint32_t/*ItemID*/, std::vector<ItemSynthesis>> g_itemSyntheses{};
    inline std::vector<ChaoticSquare> g_chaoticSquares{};
}
