#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/ItemTypes.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/UserTypes.h>

// CUser::PacketGuild

namespace shaiya
{
    enum struct GuildUserStatusType : UINT8
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
    struct GuildUserStatusOutgoing
    {
        UINT16 opcode{ 0xD0C };
        GuildUserStatusType statusType;
        ULONG charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GuildJoinRequestOutgoing
    {
        UINT16 opcode{ 0xD17 };
        ULONG charId;
        UINT16 level;
        Job job;
        CharName charName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct Item0D29
    {
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT16 quality;
        Gems gems;
        UINT8 count;
        CraftName craftName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GuildBankItemListOutgoing
    {
        UINT16 opcode{ 0xD29 };
        UINT8 itemCount;
        Array<Item0D29, 50> itemList;

        constexpr static int baseLength = 3;
    };
    #pragma pack(pop)
}
