#pragma once
#include <include/shaiya/common.h>

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
    struct ItemPickIncoming
    {
        UINT16 opcode{ 0x205 };
        ULONG zoneItemId;
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
    struct ItemRemoveIncoming
    {
        UINT16 opcode{ 0x206 };
        UINT8 bag;
        UINT8 slot;
        UINT8 count;
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
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PortalEnableIncoming
    {
        UINT16 opcode{ 0x20A };
        UINT8 portalId;
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
    struct PortalUseOutgoing
    {
        UINT16 opcode{ 0x20B };
        UINT8 portalId;
        UINT16 destMapId;
        float destX;
        float destY;
        float destZ;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharacterPvPStatusOutgoing
    {
        UINT16 opcode{ 0x20E };
        PvPStatusType statType;
        UINT32 statCount;
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
    struct VetRewardLevelIncoming
    {
        UINT16 opcode{ 0x218 };
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
    struct VetKillRewardIncoming
    {
        UINT16 opcode{ 0x219 };
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
    struct VetDeathRewardIncoming
    {
        UINT16 opcode{ 0x21A };
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
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
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
        CharId killerId;
        UINT32 killCount;
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
