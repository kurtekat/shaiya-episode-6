#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_CHAT_NORMAL
    struct GameChatNormalOutgoing
    {
        uint16_t opcode{ 0x1101 };
        uint32_t senderId;
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;

        constexpr static int baseLength = 7;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_CHAT_SENDTO
    struct GameChatSendToOutgoing
    {
        uint16_t opcode{ 0x1102 };
        bool toSender;
        String<21> senderName;
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;

        constexpr static int baseLength = 25;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_CHAT_SENDALL
    struct GameChatTradeOutgoing
    {
        uint16_t opcode{ 0x1103 };
        String<21> senderName;
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;

        constexpr static int baseLength = 24;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameChatGuildOutgoing
    {
        uint16_t opcode{ 0x1104 };
        uint32_t senderId;
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;

        constexpr static int baseLength = 7;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_CHAT_SENDPARTY
    struct GameChatPartyOutgoing
    {
        uint16_t opcode{ 0x1105 };
        uint32_t senderId;
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;

        constexpr static int baseLength = 7;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_CHATE_ERROR
    struct GameChatErrorOutgoing
    {
        uint16_t opcode{ 0x1106 };
        uint8_t result{ 1 };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_CHAT_SENDALL
    struct GameChatAllOutgoing
    {
        uint16_t opcode{ 0x1108 };
        String<21> senderName;
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;

        constexpr static int baseLength = 24;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_CHAT_ZONE
    struct GameChatZoneOutgoing
    {
        uint16_t opcode{ 0x1111 };
        String<21> senderName;
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;

        constexpr static int baseLength = 24;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameChatUnionOutgoing
    {
        uint16_t opcode{ 0x1112 };
        uint32_t senderId;
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;

        constexpr static int baseLength = 7;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)
}
