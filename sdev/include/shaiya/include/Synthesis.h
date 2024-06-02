#pragma once
#include <array>
#include <map>
#include <vector>

#include <shaiya/include/common.h>

namespace shaiya
{
    constexpr auto synthesis_min_money = 100000000U;
    constexpr auto synthesis_max_money = 500000000U;
    constexpr int synthesis_min_success_rate = 100;
    constexpr int synthesis_max_success_rate = 10000;

    struct Synthesis
    {
        int successRate;
        std::array<UINT8, 24> materialType;
        std::array<UINT8, 24> materialTypeId;
        std::array<UINT8, 24> materialCount;
        UINT8 createType;
        UINT8 createTypeId;
        UINT8 createCount;

        static void init();

    private:

        static void parseMaterial(const std::string& text, std::array<UINT8, 24>& output);
    };

    inline std::map<ItemId, std::vector<Synthesis>> g_synthesis;
}
