#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ChatUserDoesNotExist
    {
        UINT16 opcode{ 0x1106 };
        UINT8 result{ 1 };
    };
    #pragma pack(pop)
}
