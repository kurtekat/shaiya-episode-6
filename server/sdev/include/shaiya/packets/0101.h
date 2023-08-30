#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct Equipment0101
    {
        Array<UINT8, ITEM_LIST_SIZE> type;
        Array<UINT8, ITEM_LIST_SIZE> typeId;
    };

    struct Character0101
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
        bool nameChange;
        bool deleted;
        CloakBadge cloakBadge;
    };
    #pragma pack(pop)
}
