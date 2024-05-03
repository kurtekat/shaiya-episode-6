#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // interval: 120000
    struct HeartbeatOutgoing
    {
        UINT16 opcode{ 0x003 };

        HeartbeatOutgoing() = default;
    };
    #pragma pack(pop)
}
