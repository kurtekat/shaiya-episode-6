#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ChatAdminAllIncoming
    {
        UINT16 opcode{ 0xF106 };
        // w/ null-terminator
        UINT16 textLength;
        // size = textLength
        Array<char, 2000> text;
    };

    // see /nt
    struct ChatAdminAllOutgoing
    {
        UINT16 opcode{ 0xF106 };
        // w/ null-terminator
        UINT16 textLength;
        // size = textLength
        Array<char, 2000> text;
    };
    #pragma pack(pop)
}
