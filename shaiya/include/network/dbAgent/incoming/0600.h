#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/network/dbAgent/DBQuickUnit.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_DB_SET_LEVELUP
    struct DBAgentSetLevelUpIncoming
    {
        uint16_t opcode{ 0x601 };
        uint32_t billingId;
        uint16_t level;
        uint32_t exp;
        uint16_t statusPoints;
        uint16_t skillPoints;
        uint16_t strength;
        uint16_t dexterity;
        uint16_t intelligence;
        uint16_t wisdom;
        uint16_t reaction;
        uint16_t luck;
        uint16_t health;
        uint16_t mana;
        uint16_t stamina;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_DB_SET_EXP
    struct DBAgentSetExpIncoming
    {
        uint16_t opcode{ 0x602 };
        uint32_t billingId;
        uint32_t exp;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_DB_SET_MONEY
    struct DBAgentSetMoneyIncoming
    {
        uint16_t opcode{ 0x603 };
        uint32_t billingId;
        uint32_t money;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_DB_SET_STATUSUP
    struct DBAgentSetStatusUpIncoming
    {
        uint16_t opcode{ 0x604 };
        uint32_t billingId;
        uint16_t statusPoints;
        uint16_t strength;
        uint16_t dexterity;
        uint16_t recovery;
        uint16_t intelligence;
        uint16_t wisdom;
        uint16_t luck;
    };
    #pragma pack(pop)

    enum struct DBAgentSetStatusExtType : uint8_t
    {
        Honor = 1,
        Vg, Cg, Og, Ig
    };

    #pragma pack(push, 1)
    // TP_DB_SET_STATUS_EXT
    struct DBAgentSetStatusExtIncoming
    {
        uint16_t opcode{ 0x605 };
        uint32_t billingId;
        DBAgentSetStatusExtType statusType;
        uint16_t value;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_DB_SET_ENERGY
    struct DBAgentSetEnergyIncoming
    {
        uint16_t opcode{ 0x606 };
        uint32_t billingId;
        uint16_t health;
        uint16_t mana;
        uint16_t stamina;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_DB_SET_MAPPOS
    struct DBAgentSetMapPosIncoming
    {
        uint16_t opcode{ 0x607 };
        uint32_t billingId;
        uint16_t mapId;
        uint16_t direction;
        float x;
        float y;
        float z;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentSetQuickSlotIncoming
    {
        uint16_t opcode{ 0x609 };
        uint32_t billingId;
        uint8_t quickSlotCount;
        Array<DBAgentQuickUnit, 128> quickSlotList;

        constexpr static int baseLength = 7;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentSetLevelIncoming
    {
        uint16_t opcode{ 0x60A };
        uint32_t billingId;
        uint32_t level;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // not implemented
    struct DBAgentSetBankMoneyIncoming
    {
        uint16_t opcode{ 0x60B };
        uint32_t billingId;
        uint32_t bankMoney;
    };
    #pragma pack(pop)

    enum struct DBAgentSetKillCountByIndex : uint8_t
    {
        Kills,
        Deaths,
        Wins,
        Losses
    };

    #pragma pack(push, 1)
    // TP_DB_SET_KILLCOUNT
    struct DBAgentSetKillCountIncoming
    {
        uint16_t opcode{ 0x60C };
        uint32_t billingId;
        DBAgentSetKillCountByIndex byIndex;
        uint32_t value;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentSetGrowIncoming
    {
        uint16_t opcode{ 0x60D };
        uint32_t billingId;
        uint32_t grow;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentSetStatusPointIncoming
    {
        uint16_t opcode{ 0x60E };
        uint32_t billingId;
        uint32_t statusPoints;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentSetSkillPointIncoming
    {
        uint16_t opcode{ 0x60F };
        uint32_t billingId;
        uint32_t skillPoints;
    };
    #pragma pack(pop)
}
