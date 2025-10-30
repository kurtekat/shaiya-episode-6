#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct HPAbility
    {
        bool applied;       //0x1378
        PAD(1);
        uint16_t skillId;   //0x137A
        uint8_t skillLv;    //0x137C
        PAD(3);
        tick32_t prevTime;  //0x1380
        // 0xC
    };
    #pragma pack(pop)

    static_assert(sizeof(HPAbility) == 0xC);
}
