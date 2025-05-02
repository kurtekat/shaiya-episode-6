#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Job.h>

namespace shaiya
{
    enum struct GameFriendAnswerResult : uint8_t
    {
        Rejected,
        Accepted,
        NotFound
    };

    #pragma pack(push, 1)
    // TPC_COMM_FRIEND_ANS
    struct GameFriendAnswerOutgoing
    {
        uint16_t opcode{ 0x2203 };
        GameFriendAnswerResult result;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_COMM_FRIEND_ADD
    struct GameFriendAddOutgoing
    {
        uint16_t opcode{ 0x2204 };
        uint32_t objectId;
        Job job;
        String<21> charName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_COMM_FRIEND_DEL
    struct FriendRemoveOutgoing
    {
        uint16_t opcode{ 0x2205 };
        uint32_t objectId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_COMM_FRIEND_MEMO
    struct GameFriendMemoOutgoing
    {
        uint16_t opcode{ 0x2206 };
        uint32_t objectId;
        // w/o null terminator
        uint8_t memoLength;
        String<51> memo;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_COMM_BLOCK_ADD
    struct GameBlockAddOutgoing
    {
        uint16_t opcode{ 0x2209 };
        uint32_t objectId;
        String<21> charName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_COMM_BLOCK_DEL
    struct GameBlockRemoveOutgoing
    {
        uint16_t opcode{ 0x220A };
        uint32_t objectId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_COMM_BLOCK_MEMO
    struct GameBlockMemoOutgoing
    {
        uint16_t opcode{ 0x220B };
        uint32_t objectId;
        // w/o null terminator
        uint8_t memoLength;
        String<51> memo;
    };
    #pragma pack(pop)

    enum struct GameBlockAnswerResult : uint8_t
    {
        Failure,
        Success
    };

    #pragma pack(push, 1)
    // TP_COMM_BLOCK_ANS
    struct GameBlockAnswerOutgoing
    {
        uint16_t opcode{ 0x220E };
        GameBlockAnswerResult result;
    };
    #pragma pack(pop)
}
