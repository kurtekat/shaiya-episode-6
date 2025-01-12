#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/UserTypes.h>

// CUser::PacketAdminCmdC

namespace shaiya
{
    #pragma pack(push, 1)
    struct AdminCmdCharacterCureIncoming
    {
        UINT16 opcode{ 0xF801 };
        CharName charName;
    };

    struct AdminCmdCharacterKickIncoming
    {
        UINT16 opcode{ 0xF804 };
        CharName charName;
    };
    #pragma pack(pop)
}
