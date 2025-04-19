#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_MAIN
    struct TP_MAIN
    {
        uint16_t opcode;
        Array<uint8_t, 2044> command;
    };
    #pragma pack(pop)
}
