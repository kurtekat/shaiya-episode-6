#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct FriendAddIncoming
    {
        UINT16 opcode{ 0x2202 };
        CharName charName;
    };
    #pragma pack(pop)
}
