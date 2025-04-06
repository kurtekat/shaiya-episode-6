#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_ADMIN_CMDS_ERROR
    struct GameAdminCmdErrorOutgoing
    {
        uint16_t opcode{ 0xF501 };
        // failure = packet opcode
        // success = 0
        uint16_t errorType;
    };
    #pragma pack(pop)
}
