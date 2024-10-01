#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Job.h>

// CUser::PacketComm (community)

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

    #pragma pack(push, 1)
    struct FriendAddOutgoing
    {
        UINT16 opcode{ 0x2204 };
        ULONG charId;
        Job job;
        CharArray<21> charName;
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
    struct FriendMemoOutgoing
    {
        UINT16 opcode{ 0x2206 };
        ULONG charId;
        // w/o null terminator
        UINT8 memoLength;
        CharArray<51> memo;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct BlockAddOutgoing
    {
        UINT16 opcode{ 0x2209 };
        ULONG charId;
        CharArray<21> charName;
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
    struct BlockMemoOutgoing
    {
        UINT16 opcode{ 0x220B };
        ULONG charId;
        // w/o null terminator
        UINT8 memoLength;
        CharArray<51> memo;
    };
    #pragma pack(pop)

    enum struct BlockAddResult : UINT8
    {
        Failure,
        Success
    };

    #pragma pack(push, 1)
    struct BlockAddResultOutgoing
    {
        UINT16 opcode{ 0x220E };
        BlockAddResult result;
    };
    #pragma pack(pop)
}
