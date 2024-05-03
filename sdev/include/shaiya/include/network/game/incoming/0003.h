#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // interval: 120000
    struct HeartbeatIncoming
    {
        UINT16 opcode{ 0x003 };
    };
    #pragma pack(pop)
}
