#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct FriendAddOutgoing
    {
        UINT16 opcode{ 0x2204 };
        ULONG charId;
        Job job;
        CharName charName;
    };
    #pragma pack(pop)
}
