#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/ItemTypes.h>
#include <shaiya/include/common/Sex.h>

// CUser::PacketMainInterface

namespace shaiya
{
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

    enum struct UserSkillGetResult : UINT8
    {
        Success,
        InsufficientPoints,
        LevelTooLowToLearn,
        UnableToLearn
    };

    #pragma pack(push, 1)
    struct UserSkillGetOutgoing
    {
        UINT16 opcode{ 0x209 };
        UserSkillGetResult result;
        UINT8 index;
        UINT16 skillId;
        UINT8 skillLv;
    };
    #pragma pack(pop)

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
    struct PortalEnableOutgoing
    {
        UINT16 opcode{ 0x20A };
        UINT8 portalId;
        PortalEnableResult result;

        PortalEnableOutgoing() = default;

        PortalEnableOutgoing(UINT8 portalId, PortalEnableResult result)
            : portalId(portalId), result(result)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserMoveDestOutgoing
    {
        UINT16 opcode{ 0x20B };
        ULONG objectId;
        UINT16 mapId;
        float x;
        float y;
        float z;

        UserMoveDestOutgoing() = default;

        UserMoveDestOutgoing(ULONG objectId, UINT16 mapId, float x, float y, float z)
            : objectId(objectId), mapId(mapId), x(x), y(y), z(z)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct NpcGateKeeperUseOutgoing
    {
        UINT16 opcode{ 0x20C };
        bool success;
        UINT32 money;

        NpcGateKeeperUseOutgoing() = default;

        NpcGateKeeperUseOutgoing(bool success, UINT32 money)
            : success(success), money(money)
        {
        }
    };
    #pragma pack(pop)

    enum struct UserPvPStatusType : UINT8
    {
        Kill,
        Death,
        Win,
        Loss
    };

    #pragma pack(push, 1)
    struct UserPvPStatusOutgoing
    {
        UINT16 opcode{ 0x20E };
        UserPvPStatusType statusType;
        UINT32 value;

        UserPvPStatusOutgoing() = default;

        UserPvPStatusOutgoing(UserPvPStatusType statusType, UINT32 value)
            : statusType(statusType), value(value)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserMoneyOutgoing
    {
        UINT16 opcode{ 0x213 };
        UINT32 money;

        UserMoneyOutgoing() = default;

        UserMoneyOutgoing(UINT32 money)
            : money(money)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct NpcVetRewardLevelOutgoing
    {
        UINT16 opcode{ 0x218 };
        UINT8 killLv;
        UINT8 deathLv;

        NpcVetRewardLevelOutgoing() = default;

        NpcVetRewardLevelOutgoing(UINT8 killLv, UINT8 deathLv)
            : killLv(killLv), deathLv(deathLv)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct NpcVetKillRewardOutgoing
    {
        UINT16 opcode{ 0x219 };
        bool success;
        UINT8 statPoint;

        NpcVetKillRewardOutgoing() = default;

        NpcVetKillRewardOutgoing(bool success, UINT8 statPoint)
            : success(success), statPoint(statPoint)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct NpcVetDeathRewardOutgoing
    {
        UINT16 opcode{ 0x21A };
        bool success;
        UINT32 money;

        NpcVetDeathRewardOutgoing() = default;

        NpcVetDeathRewardOutgoing(bool success, UINT32 money)
            : success(success), money(money)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserItemCastOutgoing
    {
        UINT16 opcode{ 0x221 };
        ULONG objectId;

        UserItemCastOutgoing() = default;

        UserItemCastOutgoing(ULONG objectId)
            : objectId(objectId)
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

        AppearanceChangeOutgoing() = default;

        AppearanceChangeOutgoing(ULONG charId, UINT8 hair, UINT8 face, UINT8 size, Sex sex)
            : charId(charId), hair(hair), face(face), size(size), sex(sex)
        {
        }
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

    enum struct ItemExpireNoticeType : UINT16
    {
        DeletedFromInventory = 883,
        DeletedFromWarehouse,
        MinutesLeftInventory,
        MinutesLeftWarehouse,
        HoursLeftInventory,
        HoursLeftWarehouse
    };

    #pragma pack(push, 1)
    struct ItemExpireNoticeOutgoing
    {
        UINT16 opcode{ 0x22F };
        UINT8 type;
        UINT8 typeId;
        UINT8 timeValue;
        ItemExpireNoticeType noticeType;

        ItemExpireNoticeOutgoing() = default;

        ItemExpireNoticeOutgoing(UINT8 type, UINT8 typeId, UINT8 timeValue, ItemExpireNoticeType noticeType)
            : type(type), typeId(typeId), timeValue(timeValue), noticeType(noticeType)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharacterHonorOutgoing
    {
        UINT16 opcode{ 0x230 };
        UINT16 honor;

        CharacterHonorOutgoing() = default;

        CharacterHonorOutgoing(UINT16 hg)
            : honor(hg)
        {
        }
    };
    #pragma pack(pop)
}
