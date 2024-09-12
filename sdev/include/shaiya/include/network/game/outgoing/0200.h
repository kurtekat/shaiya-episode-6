#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/CraftName.h>
#include <shaiya/include/common/Gems.h>
#include <shaiya/include/common/PvPStatusType.h>
#include <shaiya/include/common/Sex.h>

// CUser::PacketMainInterface

namespace shaiya
{
    enum struct ItemExpireNoticeType : UINT16
    {
        DeletedFromInventory = 883,
        DeletedFromWarehouse,
        MinutesLeftInventory,
        MinutesLeftWarehouse,
        HoursLeftInventory,
        HoursLeftWarehouse,
    };

    enum struct PortalEnableResult : UINT8
    {
        GuildInstance,
        GuildRankingBattleInactive,
        GuildRankingBattleAlreadyJoined,
        GuildRankAbove30thRequired,
        PartyInstance,
        GuildRankingBattleJoin,
        GuildHouseNotPurchased,
        GuildHouse5DayWaitTime,
        GuildHouseMaintenanceFeeNotPaid,
        PartyInstanceClosed,
        PartyMinimumCountRequired,
        FailedToEnter,
        FailedToJoinGoddessBattle,
    };

    enum struct SkillGetResult : UINT8
    {
        Success,
        InsufficientPoints,
        LevelTooLowToLearn,
        UnableToLearn
    };

    #pragma pack(push, 1)
    struct Item0204
    {
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
        UINT16 quality;
        Gems gems;
        CraftName craftName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    typedef struct ItemBagToBagOutgoing
    {
        UINT16 opcode{ 0x204 };
        Item0204 srcItem;
        Item0204 destItem;
    } ItemBagToBankOutgoing, ItemBankToBankOutgoing;
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemBankToBagOutgoing
    {
        UINT16 opcode{ 0x204 };
        Item0204 srcItem;
        Item0204 destItem;
        UINT32 money;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemPickOutgoing
    {
        UINT16 opcode{ 0x205 };
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
        UINT16 quality;
        Gems gems;
        // or '\0'
        CraftName craftName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemRemoveOutgoing
    {
        UINT16 opcode{ 0x206 };
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;

        ItemRemoveOutgoing() = default;

        ItemRemoveOutgoing(UINT8 bag, UINT8 slot, UINT8 type, UINT8 typeId, UINT8 count)
            : bag(bag), slot(slot), type(type), typeId(typeId), count(count)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct SkillGetOutgoing
    {
        UINT16 opcode{ 0x20A };
        SkillGetResult result;
        UINT8 index;
        UINT16 skillId;
        UINT8 skillLv;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PortalEnableOutgoing
    {
        UINT16 opcode{ 0x20A };
        UINT8 portalId;
        PortalEnableResult result;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserMoveDestOutgoing
    {
        UINT16 opcode{ 0x20B };
        ULONG charId;
        UINT16 mapId;
        float x;
        float y;
        float z;

        UserMoveDestOutgoing() = default;

        UserMoveDestOutgoing(ULONG charId, UINT16 mapId, float x, float y, float z)
            : charId(charId), mapId(mapId), x(x), y(y), z(z)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GateKeeperUseOutgoing
    {
        UINT16 opcode{ 0x20C };
        bool success;
        UINT32 money;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharacterPvPStatusOutgoing
    {
        UINT16 opcode{ 0x20E };
        PvPStatusType statusType;
        UINT32 value;

        CharacterPvPStatusOutgoing() = default;

        CharacterPvPStatusOutgoing(PvPStatusType statusType, UINT32 value)
            : statusType(statusType), value(value)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharacterMoneyOutgoing
    {
        UINT16 opcode{ 0x213 };
        UINT32 money;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct VetRewardLevelOutgoing
    {
        UINT16 opcode{ 0x218 };
        UINT8 killLv;
        UINT8 deathLv;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct VetKillRewardOutgoing
    {
        UINT16 opcode{ 0x219 };
        bool success;
        UINT8 statPoint;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct VetDeathRewardOutgoing
    {
        UINT16 opcode{ 0x21A };
        bool success;
        UINT32 money;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemCastOutgoing
    {
        UINT16 opcode{ 0x221 };
        ULONG charId;

        ItemCastOutgoing() = default;

        ItemCastOutgoing(ULONG charId)
            : charId(charId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct AppearanceChangeOutgoing
    {
        UINT16 opcode{ 0x226 };
        ULONG charId;
        UINT8 hair;
        UINT8 face;
        UINT8 size;
        Sex sex;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct RevengeMarkOutgoing
    {
        UINT16 opcode{ 0x229 };
        ULONG killerId;
        UINT32 killCount;

        RevengeMarkOutgoing() = default;

        RevengeMarkOutgoing(ULONG killerId, UINT32 killCount)
            : killerId(killerId), killCount(killCount)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemDurationOutgoing
    {
        UINT16 opcode{ 0x22E };
        UINT8 bag;
        UINT8 slot;
        ULONG fromDate;
        ULONG toDate;
        ULONG unknown;

        ItemDurationOutgoing() = default;

        ItemDurationOutgoing(UINT8 bag, UINT8 slot, ULONG fromDate, ULONG toDate)
            : bag(bag), slot(slot), fromDate(fromDate), toDate(toDate), unknown(0)
        {
        }

        ItemDurationOutgoing(UINT8 bag, UINT8 slot, ULONG fromDate, ULONG toDate, ULONG unknown)
            : bag(bag), slot(slot), fromDate(fromDate), toDate(toDate), unknown(unknown)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemExpireNoticeOutgoing
    {
        UINT16 opcode{ 0x22F };
        UINT8 type;
        UINT8 typeId;
        UINT8 timeValue;
        ItemExpireNoticeType noticeType;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharacterHonorOutgoing
    {
        UINT16 opcode{ 0x230 };
        UINT16 honor;
    };
    #pragma pack(pop)
}
