#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_SETPAYLETTER
    struct SessionSetPayLetterOutgoing
    {
        uint16_t opcode{ 0x105 };
        bool enable;
    };
}
