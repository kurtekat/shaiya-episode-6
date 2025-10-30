#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct MapOpenTime
    {
        // 0:6
        uint16_t dayOfWeek;
        // 0:23
        uint16_t startHour;
        // hours
        uint16_t duration;
    };
    #pragma pack(pop)

    static_assert(sizeof(MapOpenTime) == 0x6);
}
