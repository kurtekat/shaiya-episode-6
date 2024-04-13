#pragma once
#include <sdev/include/shaiya/common.h>

// CUser::PacketUserSetStatus

namespace shaiya
{
    enum struct UserSetStatusGroup
    {
        // hg
        Honor = 1,
        // vg, cg, og, ig
        Other = 2,
    };

    #pragma pack(push, 1)
    struct UserSetStatusIncoming
    {
        UINT16 opcode{ 0x601 };
        UserId userId;
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
    struct UserSetStatusExpIncoming
    {
        UINT16 opcode{ 0x602 };
        UserId userId;
        UINT32 exp;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserSetStatusMoneyIncoming
    {
        UINT16 opcode{ 0x603 };
        UserId userId;
        UINT32 money;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserSetStatusUpIncoming
    {
        UINT16 opcode{ 0x604 };
        UserId userId;
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
    struct UserSetStatusGroupIncoming
    {
        UINT16 opcode{ 0x605 };
        UserId userId;
        UserSetStatusGroup group;
        UINT16 value;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserSetStatusHpMpSpIncoming
    {
        UINT16 opcode{ 0x606 };
        UserId userId;
        UINT16 health;
        UINT16 mana;
        UINT16 stamina;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserSetStatusLocationIncoming
    {
        UINT16 opcode{ 0x607 };
        UserId userId;
        UINT16 mapId;
        UINT16 direction;
        float x;
        float y;
        float z;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserSetStatusQuickSlot
    {
        UINT8 bag;
        UINT8 slot;
        UINT8 srcBag;
        UINT16 srcSlot;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserSetStatusQuickSlotIncoming
    {
        UINT16 opcode{ 0x609 };
        UserId userId;
        UINT8 quickSlotCount;
        // size = quickSlotCount
        Array<UserSetStatusQuickSlot, 128> quickSlot;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserSetStatusLevelIncoming
    {
        UINT16 opcode{ 0x60A };
        UserId userId;
        UINT32 level;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // not implemented
    struct UserSetStatusBankMoneyIncoming
    {
        UINT16 opcode{ 0x60B };
        UserId userId;
        UINT32 bankMoney;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserSetStatusPvPIncoming
    {
        UINT16 opcode{ 0x60C };
        UserId userId;
        PvPStatusType statType;
        UINT32 statCount;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserSetStatusGrowIncoming
    {
        UINT16 opcode{ 0x60D };
        UserId userId;
        UINT32 grow;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserSetStatusSkillPointIncoming
    {
        UINT16 opcode{ 0x60E };
        UserId userId;
        UINT32 skillPoint;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserSetStatusStatPointIncoming
    {
        UINT16 opcode{ 0x60F };
        UserId userId;
        UINT32 statPoint;
    };
    #pragma pack(pop)
}
