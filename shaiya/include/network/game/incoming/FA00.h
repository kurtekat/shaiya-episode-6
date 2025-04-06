#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/UserTypes.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct GameAdminCmdFindCharIncoming
    {
        uint16_t opcode{ 0xFA08 };
        CharName charName;
    };

    struct GameAdminCmdChatBanEnableIncoming
    {
        uint16_t opcode{ 0xFA0D };
        // not implemented
        uint16_t unknown{ 0 };
        CharName charName;
    };

    struct GameAdminCmdChatBanDisableIncoming
    {
        uint16_t opcode{ 0xFA0E };
        CharName charName;
    };

    struct GameAdminCmdMoveBanEnableIncoming
    {
        uint16_t opcode{ 0xFA0F };
        // not implemented
        uint16_t unknown{ 0 };
        CharName charName;
    };

    struct GameAdminCmdMoveBanDisableIncoming
    {
        uint16_t opcode{ 0xFA10 };
        CharName charName;
    };
    #pragma pack(pop)
}
