#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct HeartbeatIncoming
    {
        UINT16 opcode{ 0x003 };

        HeartbeatIncoming() = default;

        constexpr int interval() { return 120000; }
    };
    #pragma pack(pop)
}
