#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct RewardItemClaimIncoming
    {
        UINT16 opcode{ 0x1F04 };
    };
    #pragma pack(pop)
}
