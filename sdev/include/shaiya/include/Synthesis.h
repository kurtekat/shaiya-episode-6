#pragma once
#include <array>
#include <map>
#include <vector>

#include <shaiya/include/common.h>

namespace shaiya
{
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
