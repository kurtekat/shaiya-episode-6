#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct VetManagerKillRewardIncoming
    {
        UINT16 opcode{ 0x219 };
    };

    struct VetManagerKillRewardOutgoing
    {
        UINT16 opcode{ 0x219 };
        bool success;
        UINT8 statPoints;
    };
    #pragma pack(pop)
}
