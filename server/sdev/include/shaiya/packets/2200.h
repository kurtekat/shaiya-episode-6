#pragma once
#include <include/shaiya/common.h>

// CUser::PacketComm (community)

namespace shaiya
{
    #pragma pack(push, 1)
    enum struct FriendAddResult : UINT8
    {
        Rejected,
        Accepted,
        NotFound
    };

    enum struct BlockAddResult : UINT8
    {
        Failure,
        Success
    };

    struct FriendAddIncoming
    {
        UINT16 opcode{ 0x2202 };
        CharName charName;
    };

    struct FriendAddResultOutgoing
    {
        UINT16 opcode{ 0x2203 };
        FriendAddResult result;
    };

    struct FriendAddOutgoing
    {
        UINT16 opcode{ 0x2204 };
        ULONG charId;
        Job job;
        CharName charName;
    };

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

    struct BlockAddIncoming
    {
        UINT16 opcode{ 0x2209 };
        CharName charName;
    };

    struct BlockAddOutgoing
    {
        UINT16 opcode{ 0x2209 };
        ULONG charId;
        CharName charName;
    };

    struct BlockRemoveIncoming
    {
        UINT16 opcode{ 0x220A };
        ULONG charId;
    };

    struct BlockRemoveOutgoing
    {
        UINT16 opcode{ 0x220A };
        ULONG charId;
    };

    struct BlockSaveMemoIncoming
    {
        UINT16 opcode{ 0x220B };
        ULONG charId;
        // w/ null terminator
        UINT8 memoLength;
        Array<char, 51> memo;
    };

    struct BlockSaveMemoOutgoing
    {
        UINT16 opcode{ 0x220B };
        ULONG charId;
        // w/o null terminator
        UINT8 memoLength;
        Array<char, 51> memo;
    };

    struct BlockAddResultOutgoing
    {
        UINT16 opcode{ 0x220E };
        BlockAddResult result;
    };
    #pragma pack(pop)
}
