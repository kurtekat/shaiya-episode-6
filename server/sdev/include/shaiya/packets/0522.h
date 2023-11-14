#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct UserKillCountOutgoing
    {
        UINT16 opcode{ 0x522 };
        ULONG charId;
        UINT32 kills;
    };
    #pragma pack(pop)
}
