#pragma once
#include <strsafe.h>
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ChatNormalOutgoing
    {
        UINT16 opcode{ 0x1101 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        ChatNormalOutgoing() = delete;

        ChatNormalOutgoing(const char* message)
            : messageLength(0), message{}
        {
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr int size_without_message() { return 3; }
        constexpr int length() { return size_without_message() + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatWhisperOutgoing
    {
        UINT16 opcode{ 0x1102 };
        CharArray<21> senderName;
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        ChatWhisperOutgoing() = delete;

        ChatWhisperOutgoing(const char* senderName, const char* message)
            : messageLength(0), senderName{}, message {}
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
    struct ChatTradeOutgoing
    {
        UINT16 opcode{ 0x1103 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        ChatTradeOutgoing() = delete;

        ChatTradeOutgoing(const char* message)
            : messageLength(0), message{}
        {
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr int size_without_message() { return 3; }
        constexpr int length() { return size_without_message() + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatGuildOutgoing
    {
        UINT16 opcode{ 0x1104 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        ChatGuildOutgoing() = delete;

        ChatGuildOutgoing(const char* message)
            : messageLength(0), message{}
        {
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr int size_without_message() { return 3; }
        constexpr int length() { return size_without_message() + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatPartyOutgoing
    {
        UINT16 opcode{ 0x1105 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        ChatPartyOutgoing() = delete;

        ChatPartyOutgoing(const char* message)
            : messageLength(0), message{}
        {
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr int size_without_message() { return 3; }
        constexpr int length() { return size_without_message() + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatAreaOutgoing
    {
        UINT16 opcode{ 0x1111 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        ChatAreaOutgoing() = delete;

        ChatAreaOutgoing(const char* message)
            : messageLength(0), message{}
        {
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr int size_without_message() { return 3; }
        constexpr int length() { return size_without_message() + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatRaidOutgoing
    {
        UINT16 opcode{ 0x1112 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        ChatRaidOutgoing() = delete;

        ChatRaidOutgoing(const char* message)
            : messageLength(0), message{}
        {
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr int size_without_message() { return 3; }
        constexpr int length() { return size_without_message() + this->messageLength; }
    };
    #pragma pack(pop)
}
