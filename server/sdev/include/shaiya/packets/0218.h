#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct PvPRewardLevelIncoming
    {
        UINT16 opcode{ 0x218 };
    };

    struct PvPRewardLevelOutgoing
    {
        UINT16 opcode{ 0x218 };
        UINT8 killLv;
        UINT8 deathLv;
    };
    #pragma pack(pop)
}
