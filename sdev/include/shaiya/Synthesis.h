#pragma once
#include <map>
#include <vector>
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    class Synthesis
    {
    public:

        int32_t successRate;
        Array<uint8_t, 24> materialType;
        Array<uint8_t, 24> materialTypeId;
        Array<uint8_t, 24> materialCount;
        int32_t newItemType;
        int32_t newItemTypeId;
        int32_t newItemCount;

        static void init();

        static constexpr uint32_t goldPerPercentage = 100'000'000;
        static constexpr uint32_t goldPerPercentage5x = goldPerPercentage * 5;
    };
    #pragma pack(pop)

    inline std::map<uint32_t, std::vector<Synthesis>> g_synthesis;
}
