#pragma once
#include <include/shaiya/common.h>

// CUser::PacketMainInterface

namespace shaiya
{
    #pragma pack(push, 1)
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

    struct ItemBagToBagIncoming
    {
        UINT16 opcode{ 0x204 };
        UINT8 srcBag;
        UINT8 srcSlot;
        UINT8 destBag;
        UINT8 destSlot;
        // warehouse
        ULONG npcId;
    };

    typedef struct ItemBagToBagOutgoing
    {
        UINT16 opcode{ 0x204 };
        Item0204 srcItem;
        Item0204 destItem;
    } ItemBagToBankOutgoing, ItemBankToBankOutgoing;

    struct ItemBankToBagOutgoing
    {
        UINT16 opcode{ 0x204 };
        Item0204 srcItem;
        Item0204 destItem;
        UINT32 money;
    };

    struct ItemPickIncoming
    {
        UINT16 opcode{ 0x205 };
        ULONG zoneItemId;
    };

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

    struct ItemRemoveIncoming
    {
        UINT16 opcode{ 0x206 };
        UINT8 bag;
        UINT8 slot;
        UINT8 count;
    };

    struct ItemRemoveOutgoing
    {
        UINT16 opcode{ 0x206 };
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
    };

    struct PortalEnableIncoming
    {
        UINT16 opcode{ 0x20A };
        UINT8 portalId;
    };

    struct PortalEnableOutgoing
    {
        UINT16 opcode{ 0x20A };
        UINT8 portalId;
        PortalEnableResult result;
    };

    struct PortalUseOutgoing
    {
        UINT16 opcode{ 0x20B };
        UINT8 portalId;
        UINT16 destMapId;
        float destX;
        float destY;
        float destZ;
    };

    struct KillPCOutgoing
    {
        UINT16 opcode{ 0x20E };
        KillPC killPC;
        UINT32 kills;
    };

    struct CharacterMoneyOutgoing
    {
        UINT16 opcode{ 0x213 };
        UINT32 money;
    };

    struct VetRewardLevelIncoming
    {
        UINT16 opcode{ 0x218 };
    };

    struct VetRewardLevelOutgoing
    {
        UINT16 opcode{ 0x218 };
        UINT8 killLv;
        UINT8 deathLv;
    };

    struct VetKillRewardIncoming
    {
        UINT16 opcode{ 0x219 };
    };

    struct VetKillRewardOutgoing
    {
        UINT16 opcode{ 0x219 };
        bool success;
        UINT8 statPoint;
    };

    struct VetDeathRewardIncoming
    {
        UINT16 opcode{ 0x21A };
    };

    struct VetDeathRewardOutgoing
    {
        UINT16 opcode{ 0x21A };
        bool success;
        UINT32 money;
    };

    struct ItemCastOutgoing
    {
        UINT16 opcode{ 0x221 };
        ULONG charId;
    };

    struct AppearanceChangeIncoming
    {
        UINT16 opcode{ 0x226 };
        UINT8 bag;
        UINT8 slot;
        UINT8 hair;
        UINT8 face;
        UINT8 size;
        Sex sex;
    };

    struct AppearanceChangeOutgoing
    {
        UINT16 opcode{ 0x226 };
        ULONG charId;
        UINT8 hair;
        UINT8 face;
        UINT8 size;
        Sex sex;
    };

    struct RevengeMarkOutgoing
    {
        UINT16 opcode{ 0x229 };
        CharId killerId;
        UINT32 killCount;
    };

    struct ItemDurationOutgoing
    {
        UINT16 opcode{ 0x22E };
        UINT8 bag;
        UINT8 slot;
        ULONG fromDate;
        ULONG toDate;
        ULONG unknown;
    };

    struct ItemExpireNoticeOutgoing
    {
        UINT16 opcode{ 0x22F };
        UINT8 type;
        UINT8 typeId;
        UINT8 timeValue;
        ItemExpireNoticeType noticeType;
    };

    struct CharacterHonorOutgoing
    {
        UINT16 opcode{ 0x230 };
        UINT16 honor;
    };
    #pragma pack(pop)
}
