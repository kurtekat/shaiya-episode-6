#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ChatPartyIncoming
    {
        UINT16 opcode{ 0x1105 };
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };

    struct ChatPartyOutgoing
    {
        UINT16 opcode{ 0x1105 };
        ULONG charId;
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };
    #pragma pack(pop)
}
