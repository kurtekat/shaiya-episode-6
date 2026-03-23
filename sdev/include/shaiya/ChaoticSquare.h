#pragma once
#include <array>
#include <cstdint>
#include <vector>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ChaoticSquareResult
    {
        uint8_t type;
        uint8_t typeId;
        uint8_t count;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChaoticSquareRecipe
    {
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
    class ChaoticSquare
    {
    public:

        uint32_t itemId;
        std::array<ChaoticSquareResult, 24> results;
        std::vector<ChaoticSquareRecipe> recipes;

        static ChaoticSquare* Find(uint32_t itemId);
    };
    #pragma pack(pop)

    inline std::vector<ChaoticSquare> g_chaoticSquares{};
    inline uint32_t g_chaoticSquareFortuneMoney{ 100'000'000 };
}
