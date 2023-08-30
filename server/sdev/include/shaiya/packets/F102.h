#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ChatAdminWhisperIncoming
    {
        UINT16 opcode{ 0xF102 };
        CharName senderName;
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };

    struct ChatAdminWhisperOutgoing
    {
        UINT16 opcode{ 0xF102 };
        bool isToSender;
        CharName senderName;
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };
    #pragma pack(pop)
}
