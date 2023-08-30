#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/CFriend.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct FriendSaveMemoIncoming
    {
        UINT16 opcode{ 0x2206 };
        ULONG charId;
        // w/ null terminator
        UINT8 memoLength;
        Memo memo;
    };

    struct FriendSaveMemoOutgoing
    {
        UINT16 opcode{ 0x2206 };
        ULONG charId;
        // w/o null terminator
        UINT8 memoLength;
        Memo memo;
    };
    #pragma pack(pop)
}
