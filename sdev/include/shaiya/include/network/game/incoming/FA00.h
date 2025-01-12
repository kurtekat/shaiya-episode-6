#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/UserTypes.h>

// CUser::PacketAdminCmdE

namespace shaiya
{
    #pragma pack(push, 1)
    struct AdminCmdFindCharacterIncoming
    {
        UINT16 opcode{ 0xFA08 };
        CharName charName;
    };

    struct AdminCmdChatBanEnableIncoming
    {
        UINT16 opcode{ 0xFA0D };
        // not implemented
        UINT16 unknown{ 0 };
        CharName charName;
    };

    struct AdminCmdChatBanDisableIncoming
    {
        UINT16 opcode{ 0xFA0E };
        CharName charName;
    };

    struct AdminCmdMoveBanEnableIncoming
    {
        UINT16 opcode{ 0xFA0F };
        // not implemented
        UINT16 unknown{ 0 };
        CharName charName;
    };

    struct AdminCmdMoveBanDisableIncoming
    {
        UINT16 opcode{ 0xFA10 };
        CharName charName;
    };
    #pragma pack(pop)
}
