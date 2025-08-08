#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct GameChatNormalIncoming
    {
        uint16_t opcode{ 0x1101 };
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_CHAT_SENDTO
    struct GameChatSendToIncoming
    {
        uint16_t opcode{ 0x1102 };
        String<21> senderName;
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_CHAT_SENDALL
    struct GameChatTradeIncoming
    {
        uint16_t opcode{ 0x1103 };
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameChatGuildIncoming
    {
        uint16_t opcode{ 0x1104 };
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_CHAT_SENDPARTY
    struct GameChatPartyIncoming
    {
        uint16_t opcode{ 0x1105 };
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameChatZoneIncoming
    {
        uint16_t opcode{ 0x1111 };
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameChatUnionIncoming
    {
        uint16_t opcode{ 0x1112 };
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;
    };
    #pragma pack(pop)
}
