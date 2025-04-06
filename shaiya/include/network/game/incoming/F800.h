#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/UserTypes.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct GameAdminCmdCharCureIncoming
    {
        uint16_t opcode{ 0xF801 };
        CharName charName;
    };

    struct GameAdminCmdCharKickIncoming
    {
        uint16_t opcode{ 0xF804 };
        CharName charName;
    };
    #pragma pack(pop)
}
