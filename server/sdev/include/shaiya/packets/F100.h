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
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };

    struct AdminChatNormalOutgoing
    {
        UINT16 opcode{ 0xF101 };
        ULONG charId;
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };

    struct AdminChatWhisperIncoming
    {
        UINT16 opcode{ 0xF102 };
        CharName senderName;
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };

    struct AdminChatWhisperOutgoing
    {
        UINT16 opcode{ 0xF102 };
        bool isToSender;
        CharName senderName;
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };

    struct AdminChatTradeIncoming
    {
        UINT16 opcode{ 0xF103 };
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };

    struct AdminChatTradeOutgoing
    {
        UINT16 opcode{ 0xF103 };
        CharName senderName;
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };

    struct AdminChatGuildIncoming
    {
        UINT16 opcode{ 0xF104 };
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };

    struct AdminChatGuildOutgoing
    {
        UINT16 opcode{ 0xF104 };
        ULONG charId;
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };

    struct AdminChatPartyIncoming
    {
        UINT16 opcode{ 0xF105 };
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };

    struct AdminChatPartyOutgoing
    {
        UINT16 opcode{ 0xF105 };
        ULONG charId;
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };

    struct AdminChatAllIncoming
    {
        UINT16 opcode{ 0xF106 };
        // w/ null-terminator
        UINT16 textLength;
        // size = textLength
        Array<char, 2000> text;
    };

    // see /nt
    struct AdminChatAllOutgoing
    {
        UINT16 opcode{ 0xF106 };
        // w/ null-terminator
        UINT16 textLength;
        // size = textLength
        Array<char, 2000> text;
    };
    #pragma pack(pop)
}
