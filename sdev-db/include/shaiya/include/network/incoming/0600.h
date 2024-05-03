#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/PvPStatusType.h>

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
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentSetExpIncoming
    {
        UINT16 opcode{ 0x602 };
        ULONG userId;
        UINT32 exp;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentSetMoneyIncoming
    {
        UINT16 opcode{ 0x603 };
        ULONG userId;
        UINT32 money;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
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
    struct DBAgentSetQuickSlotIncoming
    {
        UINT16 opcode{ 0x609 };
        ULONG userId;
        UINT8 quickSlotCount;
        Array<DBAgentSetQuickSlot, 128> quickSlotList;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentSetLevelIncoming
    {
        UINT16 opcode{ 0x60A };
        ULONG userId;
        UINT32 level;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // not implemented
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
        PvPStatusType statusType;
        UINT32 value;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentSetGrowIncoming
    {
        UINT16 opcode{ 0x60D };
        ULONG userId;
        UINT32 grow;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentSetSkillPointIncoming
    {
        UINT16 opcode{ 0x60E };
        ULONG userId;
        UINT32 skillPoint;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentSetStatPointIncoming
    {
        UINT16 opcode{ 0x60F };
        ULONG userId;
        UINT32 statPoint;
    };
    #pragma pack(pop)
}
