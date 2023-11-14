#pragma once
#include <sdev/include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SaveKillPCIncoming
    {
        UINT16 opcode{ 0x60C };
        UserId userId;
        KillPC killPC;
        UINT32 kills;
    };
    #pragma pack(pop)
}
