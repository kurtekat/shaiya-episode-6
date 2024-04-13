#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #define HEARTBEAT_INTERVAL 120000

    #pragma pack(push, 1)
    struct HeartbeatIncoming
    {
        UINT16 opcode{ 0x003 };
    };
    #pragma pack(pop)
}
