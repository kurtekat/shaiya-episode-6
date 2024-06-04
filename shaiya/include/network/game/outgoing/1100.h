#pragma once
#include <array>
#include <strsafe.h>
#include <shaiya/include/common.h>
#include <shaiya/include/user/CharName.h>

// CUser::PacketChatE

namespace shaiya
{
    using ChatMessage = std::array<char, 128>;

    #pragma pack(push, 1)
    struct ChatNormalOutgoing
    {
        UINT16 opcode{ 0x1101 };
        ULONG senderId;
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;

        ChatNormalOutgoing() = default;

        ChatNormalOutgoing(ULONG senderId, const char* message)
            : senderId(senderId), messageLength(0), message{}
        {
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr int size_without_message() { return 7; }
        constexpr int length() { return size_without_message() + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatWhisperOutgoing
    {
        UINT16 opcode{ 0x1102 };
        bool isToSender;
        CharName senderName;
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;

        ChatWhisperOutgoing() = default;

        ChatWhisperOutgoing(bool isToSender, const char* senderName, const char* message)
            : isToSender(isToSender), senderName{}, messageLength(0), message{}
        {
            StringCbCopyA(this->senderName.data(), this->senderName.size(), senderName);
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr int size_without_message() { return 25; }
        constexpr int length() { return size_without_message() + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatTradeOutgoing
    {
        UINT16 opcode{ 0x1103 };
        CharName senderName;
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;

        ChatTradeOutgoing() = default;

        ChatTradeOutgoing(const char* senderName, const char* message)
            : senderName{}, messageLength(0), message{}
        {
            StringCbCopyA(this->senderName.data(), this->senderName.size(), senderName);
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr int size_without_message() { return 24; }
        constexpr int length() { return size_without_message() + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatGuildOutgoing
    {
        UINT16 opcode{ 0x1104 };
        ULONG senderId;
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;

        ChatGuildOutgoing() = default;

        ChatGuildOutgoing(ULONG senderId, const char* message)
            : senderId(senderId), messageLength(0), message{}
        {
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr int size_without_message() { return 7; }
        constexpr int length() { return size_without_message() + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatPartyOutgoing
    {
        UINT16 opcode{ 0x1105 };
        ULONG senderId;
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;

        ChatPartyOutgoing() = default;

        ChatPartyOutgoing(ULONG senderId, const char* message)
            : senderId(senderId), messageLength(0), message{}
        {
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr int size_without_message() { return 7; }
        constexpr int length() { return size_without_message() + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatUserDoesNotExistOutgoing
    {
        UINT16 opcode{ 0x1106 };
        UINT8 result{ 1 };

        ChatUserDoesNotExistOutgoing() = default;

        ChatUserDoesNotExistOutgoing(UINT8 result)
            : result(result)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatMessageToServerOutgoing
    {
        UINT16 opcode{ 0x1108 };
        CharName senderName;
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;

        ChatMessageToServerOutgoing() = default;

        ChatMessageToServerOutgoing(const char* senderName, const char* message)
            : senderName{}, messageLength(0), message{}
        {
            StringCbCopyA(this->senderName.data(), this->senderName.size(), senderName);
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr int size_without_message() { return 24; }
        constexpr int length() { return size_without_message() + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatAreaOutgoing
    {
        UINT16 opcode{ 0x1111 };
        CharName senderName;
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;

        ChatAreaOutgoing() = default;

        ChatAreaOutgoing(const char* senderName, const char* message)
            : senderName{}, messageLength(0), message{}
        {
            StringCbCopyA(this->senderName.data(), this->senderName.size(), senderName);
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr int size_without_message() { return 24; }
        constexpr int length() { return size_without_message() + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatRaidOutgoing
    {
        UINT16 opcode{ 0x1112 };
        ULONG senderId;
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;

        ChatRaidOutgoing() = default;

        ChatRaidOutgoing(ULONG senderId, const char* message)
            : senderId(senderId), messageLength(0), message{}
        {
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr int size_without_message() { return 7; }
        constexpr int length() { return size_without_message() + this->messageLength; }
    };
    #pragma pack(pop)
}
