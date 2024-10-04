#pragma once
#include <shaiya/include/common.h>

// CUser::PacketAdminCmdC

namespace shaiya
{
    #pragma pack(push, 1)
    struct AdminCmdCharCureIncoming
    {
        UINT16 opcode{ 0xF801 };
        CharArray<21> charName;
    };

    struct AdminCmdCharKickIncoming
    {
        UINT16 opcode{ 0xF804 };
        CharArray<21> charName;
    };
    #pragma pack(pop)
}
