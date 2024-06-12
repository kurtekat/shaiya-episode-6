#pragma once
#include <strsafe.h>
#include <shaiya/include/common.h>

// CUser::PacketAdminChat

namespace shaiya
{
    #pragma pack(push, 1)
    struct AdminChatNormalIncoming
    {
        UINT16 opcode{ 0xF101 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        AdminChatNormalIncoming() = delete;

        AdminChatNormalIncoming(const char* message)
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
    struct AdminChatWhisperIncoming
    {
        UINT16 opcode{ 0xF102 };
        CharArray<21> senderName;
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        AdminChatWhisperIncoming() = delete;

        AdminChatWhisperIncoming(const char* senderName, const char* message)
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
    struct AdminChatTradeIncoming
    {
        UINT16 opcode{ 0xF103 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        AdminChatTradeIncoming() = delete;

        AdminChatTradeIncoming(const char* message)
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
    struct AdminChatGuildIncoming
    {
        UINT16 opcode{ 0xF104 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        AdminChatGuildIncoming() = delete;

        AdminChatGuildIncoming(const char* message)
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
    struct AdminChatPartyIncoming
    {
        UINT16 opcode{ 0xF105 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        AdminChatPartyIncoming() = delete;

        AdminChatPartyIncoming(const char* message)
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
    struct AdminChatAllIncoming
    {
        UINT16 opcode{ 0xF106 };
        // w/ null-terminator
        UINT16 messageLength;
        CharArray<2000> message;

        AdminChatAllIncoming() = delete;

        AdminChatAllIncoming(const char* message)
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
