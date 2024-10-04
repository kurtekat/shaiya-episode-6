#pragma once
#include <shaiya/include/common.h>

// CUser::PacketAdminCmdE

namespace shaiya
{
    #pragma pack(push, 1)
    struct AdminCmdFindCharIncoming
    {
        UINT16 opcode{ 0xFA08 };
        CharArray<21> charName;
    };

    struct AdminCmdChatBanEnableIncoming
    {
        UINT16 opcode{ 0xFA0D };
        // not implemented
        UINT16 unknown{ 0 };
        CharArray<21> charName;
    };

    struct AdminCmdChatBanDisableIncoming
    {
        UINT16 opcode{ 0xFA0E };
        CharArray<21> charName;
    };

    struct AdminCmdMoveBanEnableIncoming
    {
        UINT16 opcode{ 0xFA0F };
        // not implemented
        UINT16 unknown{ 0 };
        CharArray<21> charName;
    };

    struct AdminCmdMoveBanDisableIncoming
    {
        UINT16 opcode{ 0xFA10 };
        CharArray<21> charName;
    };
    #pragma pack(pop)
}
