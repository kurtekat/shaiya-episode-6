#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct UserKillPC
    {
        UINT16 opcode{ 0x20E };
        KillPC killPC;
        UINT32 kills;
    };
    #pragma pack(pop)
}
