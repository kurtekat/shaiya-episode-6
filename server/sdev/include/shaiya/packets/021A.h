#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct VetManagerDeathRewardIncoming
    {
        UINT16 opcode{ 0x21A };
    };

    struct VetManagerDeathRewardOutgoing
    {
        UINT16 opcode{ 0x21A };
        bool success;
        UINT32 money;
    };
    #pragma pack(pop)
}
