#pragma once
#include <include/shaiya/common.h>

// CUser::PacketCharacter

namespace shaiya
{
    #pragma pack(push, 1)
    struct Equipment0101
    {
        Array<UINT8, item_list_size> type;
        Array<UINT8, item_list_size> typeId;
    };

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
        Array<char, 19> charName;
        bool deleted;
        bool nameChange;
        CloakBadge cloakBadge;
    };

    struct CharacterDeleteIncoming
    {
        UINT16 opcode{ 0x103 };
        ULONG charId;
    };

    struct CharacterDeleteOutgoing
    {
        UINT16 opcode{ 0x103 };
        UINT8 unknown{ 0 };
        ULONG charId;
    };

    struct CharacterNameChangeIncoming
    {
        UINT16 opcode{ 0x10E };
        ULONG charId;
        CharName charName;
    };

    struct CharacterNameChangeOutgoing
    {
        UINT16 opcode{ 0x10E };
        bool success;
    };

    struct CharacterRestoreIncoming
    {
        UINT16 opcode{ 0x10F };
        ULONG charId;
    };

    struct CharacterRestoreOutgoing
    {
        UINT16 opcode{ 0x10F };
        UINT8 unknown{ 0 };
        ULONG charId;
    };

    struct ServerTimeOutgoing
    {
        UINT16 opcode{ 0x115 };
        ULONG time;
    };

    struct CharNameAvailableIncoming
    {
        UINT16 opcode{ 0x119 };
        Array<char, 19> name;
    };

    struct CharNameAvailableOutgoing
    {
        UINT16 opcode{ 0x119 };
        bool available;
    };
    #pragma pack(pop)
}
