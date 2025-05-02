#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TPC_COMM_FRIEND_REQ
    struct GameFriendRequestIncoming
    {
        uint16_t opcode{ 0x2202 };
        String<21> charName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameFriendRemoveIncoming
    {
        uint16_t opcode{ 0x2205 };
        uint32_t charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameFriendMemoIncoming
    {
        uint16_t opcode{ 0x2206 };
        uint32_t charId;
        // w/ null terminator
        uint8_t memoLength;
        String<51> memo;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_COMM_BLOCK_ADD
    struct GameBlockAddIncoming
    {
        uint16_t opcode{ 0x2209 };
        String<21> charName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameBlockRemoveIncoming
    {
        uint16_t opcode{ 0x220A };
        uint32_t charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameBlockMemoIncoming
    {
        uint16_t opcode{ 0x220B };
        uint32_t charId;
        // w/ null terminator
        uint8_t memoLength;
        String<51> memo;
    };
    #pragma pack(pop)
}
