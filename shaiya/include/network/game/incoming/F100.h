#pragma once
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
        ChatMessage message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct AdminChatWhisperIncoming
    {
        UINT16 opcode{ 0xF102 };
        CharName senderName;
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct AdminChatTradeIncoming
    {
        UINT16 opcode{ 0xF103 };
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct AdminChatGuildIncoming
    {
        UINT16 opcode{ 0xF104 };
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct AdminChatPartyIncoming
    {
        UINT16 opcode{ 0xF105 };
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct AdminChatAllIncoming
    {
        UINT16 opcode{ 0xF106 };
        // w/ null-terminator
        UINT16 messageLength;
        std::array<char, 2000> message;
    };
    #pragma pack(pop)
}
