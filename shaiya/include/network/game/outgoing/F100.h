#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_CHAT_NORMAL
    struct GameAdminChatNormalOutgoing
    {
        uint16_t opcode{ 0xF101 };
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
    struct GameAdminChatSendToOutgoing
    {
        uint16_t opcode{ 0xF102 };
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
    struct GameAdminChatTradeOutgoing
    {
        uint16_t opcode{ 0xF103 };
        String<21> senderName;
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;

        constexpr static int baseLength = 24;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_CHAT_SENDMAP
    struct GameAdminChatGuildOutgoing
    {
        uint16_t opcode{ 0xF104 };
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
    struct GameAdminChatPartyOutgoing
    {
        uint16_t opcode{ 0xF105 };
        uint32_t senderId;
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;

        constexpr static int baseLength = 7;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_ADMIN_NOTIFY
    struct GameAdminNotifyOutgoing
    {
        uint16_t opcode{ 0xF106 };
        // w/ null-terminator
        uint16_t messageLength;
        String<2000> message;

        constexpr static int baseLength = 4;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)
}
