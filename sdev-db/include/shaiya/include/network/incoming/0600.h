#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Grow.h>

// CUser::PacketUserSetStatus

namespace shaiya
{
    #pragma pack(push, 1)
    struct DBAgentStatusIncoming
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
    struct DBAgentExpIncoming
    {
        UINT16 opcode{ 0x602 };
        ULONG userId;
        UINT32 exp;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentMoneyIncoming
    {
        UINT16 opcode{ 0x603 };
        ULONG userId;
        UINT32 money;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentStatusUpIncoming
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
    struct DBAgentStatusGroupIncoming
    {
        UINT16 opcode{ 0x605 };
        ULONG userId;
        enum struct
            GroupType : UINT8 {
            Honor = 1, // hg
            Other = 2, // vg, cg, og, ig
        } groupType;
        UINT16 value;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentHpMpSpIncoming
    {
        UINT16 opcode{ 0x606 };
        ULONG userId;
        UINT16 health;
        UINT16 mana;
        UINT16 stamina;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentLocationIncoming
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
    struct DBAgentQuickSlot
    {
        UINT8 bag;
        UINT8 slot;
        UINT8 srcBag;
        UINT16 srcSlot;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentQuickSlotIncoming
    {
        UINT16 opcode{ 0x609 };
        ULONG userId;
        UINT8 quickSlotCount;
        Array<DBAgentQuickSlot, 128> quickSlots;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentLevelIncoming
    {
        UINT16 opcode{ 0x60A };
        ULONG userId;
        UINT32 level;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // not implemented
    struct DBAgentBankMoneyIncoming
    {
        UINT16 opcode{ 0x60B };
        ULONG userId;
        UINT32 bankMoney;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentPvPStatusIncoming
    {
        UINT16 opcode{ 0x60C };
        ULONG userId;
        enum struct
            GroupType : UINT8 {
            Honor = 1, // hg
            Other = 2, // vg, cg, og, ig
        } groupType;
        UINT32 value;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentGrowIncoming
    {
        UINT16 opcode{ 0x60D };
        ULONG userId;
        UINT32 grow;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentSkillPointIncoming
    {
        UINT16 opcode{ 0x60E };
        ULONG userId;
        UINT32 skillPoint;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentStatPointIncoming
    {
        UINT16 opcode{ 0x60F };
        ULONG userId;
        UINT32 statPoint;
    };
    #pragma pack(pop)
}
