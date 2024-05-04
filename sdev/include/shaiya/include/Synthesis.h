#pragma once
#include <array>
#include <map>
#include <vector>

#include <include/shaiya/common.h>

namespace shaiya
{
    struct CUser;

    constexpr auto synthesis_min_money = 100000000U;
    constexpr auto synthesis_max_money = 500000000U;
    constexpr int synthesis_min_success_rate = 100;
    constexpr int synthesis_max_success_rate = 10000;

    struct Synthesis
    {
        int successRate;
        std::array<std::uint8_t, 24> materialType;
        std::array<std::uint8_t, 24> materialTypeId;
        std::array<std::uint8_t, 24> materialCount;
        std::uint8_t createType;
        std::uint8_t createTypeId;
        std::uint8_t createCount;

        static void init();
        static bool useMaterial(CUser* user, std::uint8_t type, std::uint8_t typeId, std::uint8_t count);

    private:

        static void parseMaterial(const std::string& text, std::array<std::uint8_t, 24>& output);
    };

    inline std::map<ItemId, std::vector<Synthesis>> g_synthesis;
}
