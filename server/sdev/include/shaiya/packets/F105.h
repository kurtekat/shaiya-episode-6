#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ChatAdminPartyIncoming
    {
        UINT16 opcode{ 0xF105 };
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };

    struct ChatAdminPartyOutgoing
    {
        UINT16 opcode{ 0xF105 };
        ULONG charId;
        // w/ null-terminator
        UINT8 textLength;
        // size = textLength
        Array<char, 128> text;
    };
    #pragma pack(pop)
}
