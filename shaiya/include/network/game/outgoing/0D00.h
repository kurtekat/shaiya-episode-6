#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/network/game/GuildBankUnit.h>
#include <shaiya/include/network/game/GuildJoinUserUnit.h>

namespace shaiya
{
    enum struct GameGuildUserStatusType : uint8_t
    {
        // 1:99 character level
        Quit = 102,
        Expelled,
        EnterWorld,
        LeaveWorld,
        EnterRankBattle,
        // > 200
        // value - 200 = authLv
        AuthLv1 = 201,
        AuthLv2,
        AuthLv3,
        AuthLv4,
        AuthLv5,
        AuthLv6,
        AuthLv7,
        AuthLv8,
        AuthLv9
        // etc.
    };

    #pragma pack(push, 1)
    // TP_GUILD_USERSTATE
    struct GameGuildUserStatusOutgoing
    {
        uint16_t opcode{ 0xD0C };
        GameGuildUserStatusType statusType;
        uint32_t charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_GUILD_JOINLISTADD
    struct GameGuildJoinListAddOutgoing
    {
        uint16_t opcode{ 0xD17 };
        GuildJoinUserUnit joinUser;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_GUILD_BANK_ITEM_LIST
    struct GameGuildBankItemListOutgoing
    {
        uint16_t opcode{ 0xD29 };
        uint8_t itemCount;
        Array<GuildBankUnit, 50> itemList;

        constexpr static int baseLength = 3;
    };
    #pragma pack(pop)
}
