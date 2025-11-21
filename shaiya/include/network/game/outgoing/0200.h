#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/CraftName.h>
#include <shaiya/include/common/Gems.h>
#include <shaiya/include/common/Sex.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_ITEM_BAGTOBAG
    typedef struct GameItemBagToBagOutgoing
    {
        uint16_t opcode{ 0x204 };
        uint8_t srcBag;
        uint8_t srcSlot;
        uint8_t srcType;
        uint8_t srcTypeId;
        uint8_t srcCount;
        uint16_t srcQuality;
        Gems srcGems;
        CraftName srcCraftName;
        uint8_t destBag;
        uint8_t destSlot;
        uint8_t destType;
        uint8_t destTypeId;
        uint8_t destCount;
        uint16_t destQuality;
        Gems destGems;
        CraftName destCraftName;
    } GameItemBagToBankOutgoing, GameItemBankToBankOutgoing;
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_ITEM_BANKTOBAG
    struct GameItemBankToBagOutgoing
    {
        uint16_t opcode{ 0x204 };
        uint8_t srcBag;
        uint8_t srcSlot;
        uint8_t srcType;
        uint8_t srcTypeId;
        uint8_t srcCount;
        uint16_t srcQuality;
        Gems srcGems;
        CraftName srcCraftName;
        uint8_t destBag;
        uint8_t destSlot;
        uint8_t destType;
        uint8_t destTypeId;
        uint8_t destCount;
        uint16_t destQuality;
        Gems destGems;
        CraftName destCraftName;
        uint32_t money;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_ITEM_GET
    struct GameItemGetOutgoing
    {
        uint16_t opcode{ 0x205 };
        uint8_t bag;
        uint8_t slot;
        uint8_t type;
        uint8_t typeId;
        uint8_t count;
        uint16_t quality;
        Gems gems;
        // or '\0'
        CraftName craftName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_ITEM_DROP
    struct GameItemDropOutgoing
    {
        uint16_t opcode{ 0x206 };
        uint8_t bag;
        uint8_t slot;
        uint8_t type;
        uint8_t typeId;
        uint8_t count;
    };
    #pragma pack(pop)

    enum struct GameUserSkillGetResult : uint8_t
    {
        Success,
        NotEnoughPoints,
        LevelTooLowToLearn,
        UnableToLearn
    };

    #pragma pack(push, 1)
    // TP_USER_GETSKILL
    struct GameUserSkillGetOutgoing
    {
        uint16_t opcode{ 0x209 };
        GameUserSkillGetResult result;
        uint8_t number;
        uint16_t skillId;
        uint8_t skillLv;
    };
    #pragma pack(pop)

    enum struct GameUserPortalUseResult : uint8_t
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
    // TPC_USER_USEPORTAL
    struct GameUserPortalUseOutgoing
    {
        uint16_t opcode{ 0x20A };
        uint8_t portalIndex;
        GameUserPortalUseResult result;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_USER_SETMAPPOS
    struct GameUserSetMapPosOutgoing
    {
        uint16_t opcode{ 0x20B };
        uint32_t objectId;
        uint16_t mapId;
        float x;
        float y;
        float z;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_USER_USEGATENPC
    struct GameUserGateKeeperUseOutgoing
    {
        uint16_t opcode{ 0x20C };
        bool success;
        uint32_t money;
    };
    #pragma pack(pop)

    enum struct GameUserKillCountByIndex : uint8_t
    {
        Kills,
        Deaths,
        Wins,
        Losses
    };

    #pragma pack(push, 1)
    // TP_USER_KILLCOUNT
    struct GameUserKillCountOutgoing
    {
        uint16_t opcode{ 0x20E };
        GameUserKillCountByIndex byIndex;
        uint32_t value;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_USER_SETRUN
    struct GameUserSetRunOutgoing
    {
        uint16_t opcode{ 0x210 };
        bool enabled;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_USER_SETMONEY
    struct GameUserSetMoneyOutgoing
    {
        uint16_t opcode{ 0x213 };
        uint32_t money;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_STATUS_RESULTINFO
    struct GameStatusResultInfoOutgoing
    {
        uint16_t opcode{ 0x218 };
        uint8_t killLv;
        uint8_t deathLv;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_STATUS_RESULTKILL
    struct GameStatusResultKillOutgoing
    {
        uint16_t opcode{ 0x219 };
        bool success;
        uint8_t statusPoints;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_STATUS_RESULTDEATH
    struct GameStatusResultDeathOutgoing
    {
        uint16_t opcode{ 0x21A };
        bool success;
        uint32_t money;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameUserItemCastOutgoing
    {
        uint16_t opcode{ 0x221 };
        uint32_t objectId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_BODYCHG
    struct GameUserBodyChangeOutgoing
    {
        uint16_t opcode{ 0x226 };
        uint32_t objectId;
        uint8_t hair;
        uint8_t face;
        uint8_t size;
        Sex sex;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameRevengeMarkOutgoing
    {
        uint16_t opcode{ 0x229 };
        uint32_t charId;
        uint32_t killCount;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameItemDurationOutgoing
    {
        uint16_t opcode{ 0x22E };
        uint8_t bag;
        uint8_t slot;
        time32_t fromDate;
        time32_t toDate;
        uint32_t unknown;
    };
    #pragma pack(pop)

    enum struct GameItemExpireNoticeType : uint16_t
    {
        DeletedFromInventory = 883,
        DeletedFromWarehouse,
        MinutesLeftInventory,
        MinutesLeftWarehouse,
        HoursLeftInventory,
        HoursLeftWarehouse
    };

    #pragma pack(push, 1)
    struct GameItemExpireNoticeOutgoing
    {
        uint16_t opcode{ 0x22F };
        uint8_t type;
        uint8_t typeId;
        uint8_t time;
        GameItemExpireNoticeType noticeType;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_CHARACTER_HONOR
    struct GameCharHonorOutgoing
    {
        uint16_t opcode{ 0x230 };
        uint16_t honor;
    };
    #pragma pack(pop)
}
