#pragma once
#include <include/shaiya/common.h>

// CUser::PacketChatE

namespace shaiya
{
    #pragma pack(push, 1)
    struct ChatNormalIncoming
    {
        UINT16 opcode{ 0x1101 };
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatNormalOutgoing
    {
        UINT16 opcode{ 0x1101 };
        ULONG charId;
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatWhisperIncoming
    {
        UINT16 opcode{ 0x1102 };
        CharName senderName;
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;
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
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatTradeIncoming
    {
        UINT16 opcode{ 0x1103 };
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;
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
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatGuildIncoming
    {
        UINT16 opcode{ 0x1104 };
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatGuildOutgoing
    {
        UINT16 opcode{ 0x1104 };
        ULONG charId;
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatPartyIncoming
    {
        UINT16 opcode{ 0x1105 };
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatPartyOutgoing
    {
        UINT16 opcode{ 0x1105 };
        ULONG charId;
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatUserDoesNotExistOutgoing
    {
        UINT16 opcode{ 0x1106 };
        UINT8 result{ 1 };
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
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatAreaIncoming
    {
        UINT16 opcode{ 0x1111 };
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;
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
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatRaidIncoming
    {
        UINT16 opcode{ 0x1112 };
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatRaidOutgoing
    {
        UINT16 opcode{ 0x1112 };
        ULONG charId;
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;
    };
    #pragma pack(pop)
}
