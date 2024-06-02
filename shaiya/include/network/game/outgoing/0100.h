#pragma once
#include <array>
#include <shaiya/include/common.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/Sex.h>

// CUser::PacketCharacter

namespace shaiya
{
    #pragma pack(push, 1)
    struct Equipment0101
    {
#ifdef SHAIYA_EP6_4_PT
        std::array<UINT8, 17> type;
        std::array<UINT8, 17> typeId;
#else
        std::array<UINT8, 8> type;
        std::array<UINT8, 8> typeId;
#endif
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharacterOutgoing
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
        Equipment0101 equipment;
        std::array<char, 19> charName;
        bool deleted;
        bool nameChange;
        CloakBadge cloakBadge;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharacterDeleteOutgoing
    {
        UINT16 opcode{ 0x103 };
        UINT8 unknown{ 0 };
        ULONG charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharacterNameChangeOutgoing
    {
        UINT16 opcode{ 0x10E };
        bool success;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharacterRestoreOutgoing
    {
        UINT16 opcode{ 0x10F };
        UINT8 unknown{ 0 };
        ULONG charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ServerTimeOutgoing
    {
        UINT16 opcode{ 0x115 };
        ULONG time;
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
