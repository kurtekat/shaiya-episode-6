#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct VetManagerRewardLevelIncoming
    {
        UINT16 opcode{ 0x218 };
    };

    struct VetManagerRewardLevelOutgoing
    {
        UINT16 opcode{ 0x218 };
        UINT8 killLv;
        UINT8 deathLv;
    };
    #pragma pack(pop)
}
