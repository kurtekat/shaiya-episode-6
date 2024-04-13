#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    // g_nPayLetterEnable 0x58799C

    #pragma pack(push, 1)
    struct PayLetterEnableOutgoing
    {
        UINT16 opcode{ 0x105 };
        bool enable;
    };
    #pragma pack(pop)
}
