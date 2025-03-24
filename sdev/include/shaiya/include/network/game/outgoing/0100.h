#pragma once
#include <strsafe.h>
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/ItemTypes.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/Sex.h>
#include <shaiya/include/common/UserTypes.h>

// CUser::PacketCharacter

namespace shaiya
{
    #pragma pack(push, 1)
    // 8 items (5.4, 6.0)
    struct CharacterOutgoing_EP5
    {
        UINT16 opcode{ 0x101 };
        UINT8 slot;
        ULONG charId;
        ULONG regDate;
        UINT16 level;
        Family family;
        Grow grow;
        UINT8 hair;
        UINT8 face;
        UINT8 size;
        Job job;
        Sex sex;
        UINT16 mapId;
        UINT16 strength;
        UINT16 dexterity;
        UINT16 reaction;
        UINT16 intelligence;
        UINT16 wisdom;
        UINT16 luck;
        UINT16 health;
        UINT16 mana;
        UINT16 stamina;
        ItemArray<8> equipment;
        CharArray<19> charName;
        bool deleted;
        bool nameChange;
        CloakBadge cloakBadge;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // 17 items (6.4)
    struct CharacterOutgoing_EP6_4
    {
        UINT16 opcode{ 0x101 };
        UINT8 slot;
        ULONG charId;
        ULONG regDate;
        UINT16 level;
        Family family;
        Grow grow;
        UINT8 hair;
        UINT8 face;
        UINT8 size;
        Job job;
        Sex sex;
        UINT16 mapId;
        UINT16 strength;
        UINT16 dexterity;
        UINT16 reaction;
        UINT16 intelligence;
        UINT16 wisdom;
        UINT16 luck;
        UINT16 health;
        UINT16 mana;
        UINT16 stamina;
        ItemArray<17> equipment;
        CharArray<19> charName;
        bool deleted;
        bool nameChange;
        CloakBadge cloakBadge;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharacterDeleteOutgoing
    {
        UINT16 opcode{ 0x103 };
        UINT8 unknown;
        ULONG charId;

        CharacterDeleteOutgoing() = default;

        CharacterDeleteOutgoing(ULONG charId)
            : unknown(0), charId(charId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharacterEnterWorldOutgoing
    {
        UINT16 opcode{ 0x104 };
        ULONG charId;

        CharacterEnterWorldOutgoing() = default;

        CharacterEnterWorldOutgoing(ULONG charId)
            : charId(charId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharacterLeaveWorldOutgoing
    {
        UINT16 opcode{ 0x107 };

        CharacterLeaveWorldOutgoing() = default;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserMaxGrowOutgoing
    {
        UINT16 opcode{ 0x109 };
        Country country;
        Grow maxGrow;

        UserMaxGrowOutgoing() = default;

        UserMaxGrowOutgoing(Country country, Grow maxGrow)
            : country(country), maxGrow(maxGrow)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserLeaveWorldOutgoing
    {
        UINT16 opcode{ 0x10D };

        UserLeaveWorldOutgoing() = default;
    };
    #pragma pack(pop)

    enum struct CharNameChangeResult : UINT8
    {
        Success = 1,
        Failure
    };

    #pragma pack(push, 1)
    struct CharNameChangeOutgoing
    {
        UINT16 opcode{ 0x10E };
        CharNameChangeResult result;

        CharNameChangeOutgoing() = default;

        CharNameChangeOutgoing(CharNameChangeResult result)
            : result(result)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharacterRestoreOutgoing
    {
        UINT16 opcode{ 0x10F };
        UINT8 unknown;
        ULONG charId;

        CharacterRestoreOutgoing() = default;

        CharacterRestoreOutgoing(ULONG charId)
            : unknown(0), charId(charId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ServerTimeOutgoing
    {
        UINT16 opcode{ 0x114 };
        ULONG timestamp;

        ServerTimeOutgoing() = default;

        ServerTimeOutgoing(ULONG timestamp)
            : timestamp(timestamp)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // timestamp = localtime + (seconds(hours) + seconds(minutes))
    struct ServerTimeCmdOutgoing
    {
        UINT16 opcode{ 0x115 };
        ULONG timestamp;

        ServerTimeCmdOutgoing() = default;

        ServerTimeCmdOutgoing(ULONG timestamp)
            : timestamp(timestamp)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct LapisianEnchantWeaponStepOutgoing
    {
        UINT16 opcode{ 0x116 };
        Array<UINT16, 21> addValue;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GuildCharNameOutgoing
    {
        UINT16 opcode{ 0x117 };
        ULONG charId;
        CharName charName;

        GuildCharNameOutgoing() = default;

        GuildCharNameOutgoing(ULONG charId,  const char* charName)
            : charId(charId), charName{}
        {
            StringCbCopyA(this->charName.data(), this->charName.size(), charName);
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharNameAvailableOutgoing
    {
        UINT16 opcode{ 0x119 };
        bool available;

        CharNameAvailableOutgoing() = default;

        CharNameAvailableOutgoing(bool available)
            : available(available)
        {
        }
    };
    #pragma pack(pop)
}
