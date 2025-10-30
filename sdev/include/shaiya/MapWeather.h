#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct MapWeather
    {
        int32_t state;      //0x00
        int32_t power;      //0x04
        int32_t rate;       //0x08
        int32_t delay;      //0x0C
        int32_t noneDelay;  //0x10
        bool currentState;  //0x14
        PAD(3);
        // 0x18
        tick32_t nextUpdateTime;
        // 0x1C
    };
    #pragma pack(pop)

    static_assert(sizeof(MapWeather) == 0x1C);
}
