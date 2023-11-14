#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct PvPDeathRewardIncoming
    {
        UINT16 opcode{ 0x21A };
    };

    struct PvPDeathRewardOutgoing
    {
        UINT16 opcode{ 0x21A };
        bool success;
        UINT32 money;
    };
    #pragma pack(pop)
}
