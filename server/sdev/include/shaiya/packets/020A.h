#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
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

    struct PortalEnableIncoming
    {
        UINT16 opcode{ 0x20A };
        UINT8 portalId;
    };

    struct PortalEnableOutgoing
    {
        UINT16 opcode{ 0x20A };
        UINT8 portalId;
        UINT8 result;
    };
    #pragma pack(pop)
}
