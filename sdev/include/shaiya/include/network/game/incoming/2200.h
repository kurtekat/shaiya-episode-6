#pragma once
#include <strsafe.h>
#include <shaiya/include/common.h>

// CUser::PacketComm (community)

namespace shaiya
{
    #pragma pack(push, 1)
    struct FriendAddIncoming
    {
        UINT16 opcode{ 0x2202 };
        CharArray<21> charName;
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
    struct FriendMemoIncoming
    {
        UINT16 opcode{ 0x2206 };
        ULONG charId;
        // w/ null terminator
        UINT8 memoLength;
        CharArray<51> memo;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct BlockAddIncoming
    {
        UINT16 opcode{ 0x2209 };
        CharArray<21> charName;
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
    struct BlockMemoIncoming
    {
        UINT16 opcode{ 0x220B };
        ULONG charId;
        // w/ null terminator
        UINT8 memoLength;
        CharArray<51> memo;
    };
    #pragma pack(pop)
}
