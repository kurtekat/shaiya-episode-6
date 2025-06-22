#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct GameAdminCmdCCharCureIncoming
    {
        uint16_t opcode{ 0xF801 };
        String<21> charName;
    };

    struct GameAdminCmdCCharKickIncoming
    {
        uint16_t opcode{ 0xF804 };
        String<21> charName;
    };
    #pragma pack(pop)
}
