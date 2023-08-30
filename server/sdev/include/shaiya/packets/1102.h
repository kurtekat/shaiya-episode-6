#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ChatWhisperIncoming
    {
        UINT16 opcode{ 0x1102 };
        CharName senderName;
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };

    struct ChatWhisperOutgoing
    {
        UINT16 opcode{ 0x1102 };
        bool isToSender;
        CharName senderName;
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };
    #pragma pack(pop)
}