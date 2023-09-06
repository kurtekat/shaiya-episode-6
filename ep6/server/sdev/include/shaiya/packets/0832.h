#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct Packet0832Response
    {
        WORD opcode; // 0x0832
        BYTE result;
    };
    #pragma pack(pop)
}
