#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct AdminCmdResultOutgoing
    {
        UINT16 opcode{ 0xF501 };
        // failure = packet opcode
        // success = 0
        UINT16 result;

        AdminCmdResultOutgoing() = default;

        AdminCmdResultOutgoing(UINT16 result)
            : result(result)
        {
        }
    };
    #pragma pack(pop)
}
