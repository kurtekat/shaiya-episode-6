#pragma once
#include <strsafe.h>
#include <shaiya/include/common.h>
#include <shaiya/include/common/UserTypes.h>

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
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatWhisperIncoming
    {
        UINT16 opcode{ 0x1102 };
        CharName senderName;
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatTradeIncoming
    {
        UINT16 opcode{ 0x1103 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatGuildIncoming
    {
        UINT16 opcode{ 0x1104 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatPartyIncoming
    {
        UINT16 opcode{ 0x1105 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatAreaIncoming
    {
        UINT16 opcode{ 0x1111 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ChatRaidIncoming
    {
        UINT16 opcode{ 0x1112 };
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;
    };
    #pragma pack(pop)
}
