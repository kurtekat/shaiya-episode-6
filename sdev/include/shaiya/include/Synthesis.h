#pragma once
#include <array>
#include <map>
#include <string>
#include <vector>

namespace shaiya
{
    using ItemId = uint32_t;

    struct Synthesis
    {
        int successRate;
        std::array<uint8_t, 24> materialType;
        std::array<uint8_t, 24> materialTypeId;
        std::array<uint8_t, 24> materialCount;
        uint8_t createType;
        uint8_t createTypeId;
        uint8_t createCount;

        static void init();

    private:

        static void parseMaterial(const std::string& text, std::array<uint8_t, 24>& output);
    };

    inline std::map<ItemId, std::vector<Synthesis>> g_synthesis;
}
