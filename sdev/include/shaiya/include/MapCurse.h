#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct MapCurse
    {
        uint16_t skillId;
        Country country;
        uint8_t addPvPKillCount;
        uint8_t addPvPKillExpPercentage;
        PAD(3);
        // 0x8
    };
    #pragma pack(pop)

    static_assert(sizeof(MapCurse) == 0x8);
}
