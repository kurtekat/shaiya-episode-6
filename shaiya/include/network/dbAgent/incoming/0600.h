#pragma once
#include <shaiya/include/common.h>
#include <sdev/include/shaiya/include/CUser.h>

// CUser::PacketUserSetStatus

namespace shaiya
{
    enum struct DBAgentSetStatusGroupType
    {
        // hg
        Honor = 1,
        // vg, cg, og, ig
        Other = 2,
    };

    enum struct DBAgentSetPvPStatusType : UINT8
    {
        Kill,   // k1
        Death,  // k2
        Win,    // k3
        Loss    // k4
    };

    #pragma pack(push, 1)
    struct DBAgentSetStatusIncoming
    {
        UINT16 opcode{ 0x601 };
        ULONG userId;
        UINT16 level;
        UINT32 exp;
        UINT16 statPoint;
        UINT16 skillPoint;
        UINT16 strength;
        UINT16 dexterity;
        UINT16 intelligence;
        UINT16 wisdom;
        UINT16 reaction;
        UINT16 luck;
        UINT16 health;
        UINT16 mana;
        UINT16 stamina;

        DBAgentSetStatusIncoming() = default;

        DBAgentSetStatusIncoming(CUser* user)
        {
            this->userId = user->userId;
            this->level = user->level;
            this->exp = user->exp;
            this->statPoint = user->statPoint;
            this->skillPoint = user->skillPoint;
            this->strength = user->strength;
            this->dexterity = user->dexterity;
            this->intelligence = user->intelligence;
            this->wisdom = user->wisdom;
            this->reaction = user->reaction;
            this->luck = user->luck;
            this->health = user->health;
            this->mana = user->mana;
            this->stamina = user->stamina;
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // use CUser::SendDBExp
    struct DBAgentSetExpIncoming
    {
        UINT16 opcode{ 0x602 };
        ULONG userId;
        UINT32 exp;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // use CUser::SendDBMoney
    struct DBAgentSetMoneyIncoming
    {
        UINT16 opcode{ 0x603 };
        ULONG userId;
        UINT32 money;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // use CUser::SendDBStatusUp
    struct DBAgentSetStatusUpIncoming
    {
        UINT16 opcode{ 0x604 };
        ULONG userId;
        UINT16 statPoint;
        UINT16 strength;
        UINT16 dexterity;
        UINT16 recovery;
        UINT16 intelligence;
        UINT16 wisdom;
        UINT16 luck;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentSetStatusGroupIncoming
    {
        UINT16 opcode{ 0x605 };
        ULONG userId;
        DBAgentSetStatusGroupType groupType;
        UINT16 value;

        DBAgentSetStatusGroupIncoming() = default;

        DBAgentSetStatusGroupIncoming(ULONG userId, DBAgentSetStatusGroupType groupType, UINT16 value)
            : userId(userId), groupType(groupType), value(value)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentSetHpMpSpIncoming
    {
        UINT16 opcode{ 0x606 };
        ULONG userId;
        UINT16 health;
        UINT16 mana;
        UINT16 stamina;

        DBAgentSetHpMpSpIncoming() = default;

        DBAgentSetHpMpSpIncoming(ULONG userId, UINT16 health, UINT16 mana, UINT16 stamina)
            : userId(userId), health(health), mana(mana), stamina(stamina)
        {
        }

        DBAgentSetHpMpSpIncoming(CUser* user)
            : userId(user->userId), health(user->health), mana(user->mana), stamina(user->stamina)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentSetLocationIncoming
    {
        UINT16 opcode{ 0x607 };
        ULONG userId;
        UINT16 mapId;
        UINT16 direction;
        float x;
        float y;
        float z;

        DBAgentSetLocationIncoming() = default;

        DBAgentSetLocationIncoming(ULONG userId, UINT16 mapId, UINT16 direction, float x, float y, float z)
            : userId(userId), mapId(mapId), direction(direction), x(x), y(y), z(z)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentSetQuickSlot
    {
        UINT8 bag;
        UINT8 slot;
        UINT8 srcBag;
        UINT16 srcSlot;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // use CUser::SendDBAgentQuickSlot
    struct DBAgentSetQuickSlotIncoming
    {
        UINT16 opcode{ 0x609 };
        ULONG userId;
        UINT8 quickSlotCount;
        Array<DBAgentSetQuickSlot, 128> quickSlotList;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // use CUser::SendDBLevel
    struct DBAgentSetLevelIncoming
    {
        UINT16 opcode{ 0x60A };
        ULONG userId;
        UINT32 level;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // not implemented
    // use CUser::SendDBBankMoney
    struct DBAgentSetBankMoneyIncoming
    {
        UINT16 opcode{ 0x60B };
        ULONG userId;
        UINT32 bankMoney;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentSetPvPStatusIncoming
    {
        UINT16 opcode{ 0x60C };
        ULONG userId;
        DBAgentSetPvPStatusType statusType;
        UINT32 value;

        DBAgentSetPvPStatusIncoming() = default;

        DBAgentSetPvPStatusIncoming(ULONG userId, DBAgentSetPvPStatusType statusType, UINT32 value)
            : userId(userId), statusType(statusType), value(value)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // use CUser::SendDBGrow
    struct DBAgentSetGrowIncoming
    {
        UINT16 opcode{ 0x60D };
        ULONG userId;
        UINT32 grow;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // use CUser::SendDBSkillPoint
    struct DBAgentSetSkillPointIncoming
    {
        UINT16 opcode{ 0x60E };
        ULONG userId;
        UINT32 skillPoint;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // use CUser::SendDBStatPoint
    struct DBAgentSetStatPointIncoming
    {
        UINT16 opcode{ 0x60F };
        ULONG userId;
        UINT32 statPoint;
    };
    #pragma pack(pop)
}
