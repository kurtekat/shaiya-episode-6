#pragma once
#include <shaiya/include/common.h>

// CUser::PacketAdminChat

namespace shaiya
{
    #pragma pack(push, 1)
    struct AdminChatNormalOutgoing
    {
        UINT16 opcode{ 0xF101 };
        ULONG charId;
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;

        constexpr int size_without_message() { return 7; }
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
        ChatMessage message;

        constexpr int size_without_message() { return 25; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct AdminChatTradeOutgoing
    {
        UINT16 opcode{ 0xF103 };
        CharName senderName;
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;

        constexpr int size_without_message() { return 24; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct AdminChatGuildOutgoing
    {
        UINT16 opcode{ 0xF104 };
        ULONG charId;
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;

        constexpr int size_without_message() { return 7; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct AdminChatPartyOutgoing
    {
        UINT16 opcode{ 0xF105 };
        ULONG charId;
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;

        constexpr int size_without_message() { return 7; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // see /nt
    struct AdminChatAllOutgoing
    {
        UINT16 opcode{ 0xF106 };
        // w/ null-terminator
        UINT16 messageLength;
        std::array<char, 2000> message;

        constexpr int size_without_message() { return 4; }
    };
    #pragma pack(pop)
}
