#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct FriendRemoveIncoming
    {
        UINT16 opcode{ 0x2205 };
        ULONG charId;
    };

    struct FriendRemoveOutgoing
    {
        UINT16 opcode{ 0x2205 };
        ULONG charId;
    };
    #pragma pack(pop)
}
