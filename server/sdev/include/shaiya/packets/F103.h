#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ChatAdminTradeIncoming
    {
        UINT16 opcode{ 0xF103 };
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };

    struct ChatAdminTradeOutgoing
    {
        UINT16 opcode{ 0xF103 };
        CharName senderName;
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };
    #pragma pack(pop)
}
