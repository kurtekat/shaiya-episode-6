#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ItemCast
    {
        UINT16 opcode{ 0x221 };
        ULONG charId;
    };
    #pragma pack(pop)
}
