#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    enum struct FriendAddResult : UINT8
    {
        Rejected,
        Accepted,
        NotFound
    };

    #pragma pack(push, 1)
    struct FriendAddResultOutgoing
    {
        UINT16 opcode{ 0x2203 };
        FriendAddResult result;
    };
    #pragma pack(pop)
}
