#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct GameAdminCmdEFindCharIncoming
    {
        uint16_t opcode{ 0xFA08 };
        String<21> charName;
    };

    struct GameAdminCmdEChatBanEnableIncoming
    {
        uint16_t opcode{ 0xFA0D };
        // not implemented
        uint16_t unknown{ 0 };
        String<21> charName;
    };

    struct GameAdminCmdEChatBanDisableIncoming
    {
        uint16_t opcode{ 0xFA0E };
        String<21> charName;
    };

    struct GameAdminCmdEMoveBanEnableIncoming
    {
        uint16_t opcode{ 0xFA0F };
        // not implemented
        uint16_t unknown{ 0 };
        String<21> charName;
    };

    struct GameAdminCmdEMoveBanDisableIncoming
    {
        uint16_t opcode{ 0xFA10 };
        String<21> charName;
    };
    #pragma pack(pop)
}
