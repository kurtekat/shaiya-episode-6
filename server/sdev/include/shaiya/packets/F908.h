#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct NoticeToIncoming
    {
        UINT16 opcode{ 0xF908 };
        CharName targetName;
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };

    struct NoticeToOutgoing
    {
        UINT16 opcode{ 0xF908 };
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };
    #pragma pack(pop)
}
