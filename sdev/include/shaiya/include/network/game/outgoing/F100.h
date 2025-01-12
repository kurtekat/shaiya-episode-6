#pragma once
#include <strsafe.h>
#include <shaiya/include/common.h>
#include <shaiya/include/common/UserTypes.h>

// CUser::PacketAdminChat

namespace shaiya
{
    #pragma pack(push, 1)
    struct AdminChatNormalOutgoing
    {
        UINT16 opcode{ 0xF101 };
        ULONG senderId;
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        AdminChatNormalOutgoing() = default;

        AdminChatNormalOutgoing(ULONG senderId, const char* message)
            : senderId(senderId), messageLength(0), message{}
        {
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr static int baseLength = 7;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct AdminChatWhisperOutgoing
    {
        UINT16 opcode{ 0xF102 };
        bool isToSender;
        CharName senderName;
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        AdminChatWhisperOutgoing() = default;

        AdminChatWhisperOutgoing(bool isToSender, const char* senderName, const char* message)
            : isToSender(isToSender), senderName{}, messageLength(0), message{}
        {
            StringCbCopyA(this->senderName.data(), this->senderName.size(), senderName);
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr static int baseLength = 25;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct AdminChatTradeOutgoing
    {
        UINT16 opcode{ 0xF103 };
        CharName senderName;
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        AdminChatTradeOutgoing() = default;

        AdminChatTradeOutgoing(const char* senderName, const char* message)
            : senderName{}, messageLength(0), message{}
        {
            StringCbCopyA(this->senderName.data(), this->senderName.size(), senderName);
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr static int baseLength = 24;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct AdminChatGuildOutgoing
    {
        UINT16 opcode{ 0xF104 };
        ULONG senderId;
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        AdminChatGuildOutgoing() = default;

        AdminChatGuildOutgoing(ULONG senderId, const char* message)
            : senderId(senderId), messageLength(0), message{}
        {
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr static int baseLength = 7;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct AdminChatPartyOutgoing
    {
        UINT16 opcode{ 0xF105 };
        ULONG senderId;
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        AdminChatPartyOutgoing() = default;

        AdminChatPartyOutgoing(ULONG senderId, const char* message)
            : senderId(senderId), messageLength(0), message{}
        {
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr static int baseLength = 7;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // see /nt
    struct AdminChatAllOutgoing
    {
        UINT16 opcode{ 0xF106 };
        // w/ null-terminator
        UINT16 messageLength;
        CharArray<2000> message;

        AdminChatAllOutgoing(const char* message)
            : messageLength(0), message{}
        {
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT16>(std::strlen(this->message.data()) + 1);
        }

        constexpr static int baseLength = 4;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)
}
