#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct GameRewardItemGetIncoming
    {
        uint16_t opcode{ 0x1F04 };
    };
    #pragma pack(pop)
}
