#pragma once
#include <strsafe.h>
#include <shaiya/include/common.h>

// CUser::PacketChatE

namespace shaiya
{
    #pragma pack(push, 1)
    struct ChatNormalIncoming
    {
        UINT16 opcode{ 0x1101 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        ChatNormalIncoming() = delete;

        ChatNormalIncoming(const char* message)
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
    struct ChatWhisperIncoming
    {
        UINT16 opcode{ 0x1102 };
        CharArray<21> senderName;
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        ChatWhisperIncoming() = delete;

        ChatWhisperIncoming(const char* senderName, const char* message)
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
    struct ChatTradeIncoming
    {
        UINT16 opcode{ 0x1103 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        ChatTradeIncoming() = delete;

        ChatTradeIncoming(const char* message)
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
    struct ChatGuildIncoming
    {
        UINT16 opcode{ 0x1104 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        ChatGuildIncoming() = delete;

        ChatGuildIncoming(const char* message)
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
    struct ChatPartyIncoming
    {
        UINT16 opcode{ 0x1105 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        ChatPartyIncoming() = delete;

        ChatPartyIncoming(const char* message)
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
    struct ChatAreaIncoming
    {
        UINT16 opcode{ 0x1111 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        ChatAreaIncoming() = delete;

        ChatAreaIncoming(const char* message)
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
    struct ChatRaidIncoming
    {
        UINT16 opcode{ 0x1112 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        ChatRaidIncoming() = delete;

        ChatRaidIncoming(const char* message)
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
