#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SendCharacterHonor
    {
        UINT16 opcode{ 0x230 };
        UINT16 honor;
    };
    #pragma pack(pop)
}
