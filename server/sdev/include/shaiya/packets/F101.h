#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ChatAdminNormalIncoming
    {
        UINT16 opcode{ 0xF101 };
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };

    struct ChatAdminNormalOutgoing
    {
        UINT16 opcode{ 0xF101 };
        ULONG charId;
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };
    #pragma pack(pop)
}
