#pragma once
#include <array>
#include <map>
#include <vector>
#include <shaiya/include/common/ItemTypes.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct Synthesis
    {
        int successRate;
        std::array<uint8_t, 24> materialType;
        std::array<uint8_t, 24> materialTypeId;
        std::array<uint8_t, 24> materialCount;
        int createType;
        int createTypeId;
        int createCount;

        static void init();
    };
    #pragma pack(pop)

    inline std::map<ItemId, std::vector<Synthesis>> g_synthesis;
}
