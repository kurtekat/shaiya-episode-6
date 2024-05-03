#pragma once
#include <strsafe.h>
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct AdminChatNormalOutgoing
    {
        UINT16 opcode{ 0xF101 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        AdminChatNormalOutgoing() = delete;

        AdminChatNormalOutgoing(const char* message)
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
    struct AdminChatWhisperOutgoing
    {
        UINT16 opcode{ 0xF102 };
        CharArray<21> senderName;
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        AdminChatWhisperOutgoing() = delete;

        AdminChatWhisperOutgoing(const char* senderName, const char* message)
            : messageLength(0), senderName{}, message{}
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
    struct AdminChatTradeOutgoing
    {
        UINT16 opcode{ 0xF103 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        AdminChatTradeOutgoing() = delete;

        AdminChatTradeOutgoing(const char* message)
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
    struct AdminChatGuildOutgoing
    {
        UINT16 opcode{ 0xF104 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        AdminChatGuildOutgoing() = delete;

        AdminChatGuildOutgoing(const char* message)
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
    struct AdminChatPartyOutgoing
    {
        UINT16 opcode{ 0xF105 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        AdminChatPartyOutgoing() = delete;

        AdminChatPartyOutgoing(const char* message)
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
    struct AdminChatAllOutgoing
    {
        UINT16 opcode{ 0xF106 };
        // w/ null-terminator
        UINT16 messageLength;
        CharArray<2000> message;

        AdminChatAllOutgoing() = delete;

        AdminChatAllOutgoing(const char* message)
            : messageLength(0), message{}
        {
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT16>(std::strlen(this->message.data()) + 1);
        }

        constexpr int size_without_message() { return 4; }
        constexpr int length() { return size_without_message() + this->messageLength; }
    };
    #pragma pack(pop)
}
