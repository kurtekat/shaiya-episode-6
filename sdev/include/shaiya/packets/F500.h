#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct AdminCmdResultOutgoing
    {
        UINT16 opcode{ 0xF501 };
        // failure = packet opcode
        // success = 0
        UINT16 result;
    };
    #pragma pack(pop)
}
