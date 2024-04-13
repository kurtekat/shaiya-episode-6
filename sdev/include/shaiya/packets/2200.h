#pragma once
#include <include/shaiya/common.h>

// CUser::PacketComm (community)

namespace shaiya
{
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

    #pragma pack(push, 1)
    struct FriendAddIncoming
    {
        UINT16 opcode{ 0x2202 };
        CharName charName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct FriendAddResultOutgoing
    {
        UINT16 opcode{ 0x2203 };
        FriendAddResult result;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct FriendAddOutgoing
    {
        UINT16 opcode{ 0x2204 };
        ULONG charId;
        Job job;
        CharName charName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct FriendRemoveIncoming
    {
        UINT16 opcode{ 0x2205 };
        ULONG charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct FriendRemoveOutgoing
    {
        UINT16 opcode{ 0x2205 };
        ULONG charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct FriendSaveMemoIncoming
    {
        UINT16 opcode{ 0x2206 };
        ULONG charId;
        // w/ null terminator
        UINT8 memoLength;
        Memo memo;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct FriendSaveMemoOutgoing
    {
        UINT16 opcode{ 0x2206 };
        ULONG charId;
        // w/o null terminator
        UINT8 memoLength;
        Memo memo;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct BlockAddIncoming
    {
        UINT16 opcode{ 0x2209 };
        CharName charName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct BlockAddOutgoing
    {
        UINT16 opcode{ 0x2209 };
        ULONG charId;
        CharName charName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct BlockRemoveIncoming
    {
        UINT16 opcode{ 0x220A };
        ULONG charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct BlockRemoveOutgoing
    {
        UINT16 opcode{ 0x220A };
        ULONG charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct BlockSaveMemoIncoming
    {
        UINT16 opcode{ 0x220B };
        ULONG charId;
        // w/ null terminator
        UINT8 memoLength;
        Memo memo;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct BlockSaveMemoOutgoing
    {
        UINT16 opcode{ 0x220B };
        ULONG charId;
        // w/o null terminator
        UINT8 memoLength;
        Memo memo;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct BlockAddResultOutgoing
    {
        UINT16 opcode{ 0x220E };
        BlockAddResult result;
    };
    #pragma pack(pop)
}
