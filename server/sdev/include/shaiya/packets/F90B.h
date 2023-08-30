#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct NoticeAllIncoming
    {
        UINT16 opcode{ 0xF90B };
        UINT16 unknown;
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };

    struct NoticeAllOutgoing
    {
        UINT16 opcode{ 0xF90B };
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };
    #pragma pack(pop)
}
