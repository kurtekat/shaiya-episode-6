#pragma once
#include <array>
#include <cstdint>
#include <vector>
#include "FailItem.h"

namespace shaiya
{
    using ItemId = uint32_t;

    #pragma pack(push, 1)
    struct ChaoticSquareRecipe
    {
        int32_t id;
        int32_t chance;
        std::array<uint8_t, 24> materialType;
        std::array<uint8_t, 24> materialTypeId;
        std::array<uint8_t, 24> materialCount;
        uint8_t resultType;
        uint8_t resultTypeId;
        uint8_t resultCount;
        bool hidden;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChaoticSquareResultList
    {
        std::array<uint8_t, 10> itemType;
        std::array<uint8_t, 10> itemTypeId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    class ChaoticSquare
    {
    public:

        ItemId itemId;
        std::array<FailItem, 24> failItemList;
        std::vector<int32_t> recipeList;
        std::vector<ChaoticSquareResultList> resultLists;

        static ChaoticSquare* Find(ItemId itemId);
        static ChaoticSquareRecipe* FindRecipe(int id);
    };
    #pragma pack(pop)

    inline std::vector<ChaoticSquareRecipe> g_chaoticSquareRecipes{};
    inline std::vector<ChaoticSquare> g_chaoticSquares{};
    inline uint32_t g_chaoticSquareFortuneMoney{ 100'000'000 };
}
