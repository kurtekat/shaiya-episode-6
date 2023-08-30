#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ChatTradeIncoming
    {
        UINT16 opcode{ 0x1103 };
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };

    struct ChatTradeOutgoing
    {
        UINT16 opcode{ 0x1103 };
        CharName senderName;
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };
    #pragma pack(pop)
}
