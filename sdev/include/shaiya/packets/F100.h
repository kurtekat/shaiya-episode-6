#pragma once
#include <include/shaiya/common.h>

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
    struct AdminChatNormalOutgoing
    {
        UINT16 opcode{ 0xF101 };
        ULONG charId;
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
    struct AdminChatWhisperOutgoing
    {
        UINT16 opcode{ 0xF102 };
        bool isToSender;
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
    struct AdminChatTradeOutgoing
    {
        UINT16 opcode{ 0xF103 };
        CharName senderName;
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
    struct AdminChatGuildOutgoing
    {
        UINT16 opcode{ 0xF104 };
        ULONG charId;
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
    struct AdminChatPartyOutgoing
    {
        UINT16 opcode{ 0xF105 };
        ULONG charId;
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
        Array<char, 2000> message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // see /nt
    struct AdminChatAllOutgoing
    {
        UINT16 opcode{ 0xF106 };
        // w/ null-terminator
        UINT16 messageLength;
        Array<char, 2000> message;
    };
    #pragma pack(pop)
}
