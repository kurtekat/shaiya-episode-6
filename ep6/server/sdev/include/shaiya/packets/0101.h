#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    #ifdef SHAIYA_EP6
    struct Equipment0101
    {
        UINT8 type[17];
        UINT8 typeId[17];
    };
    #else
    struct Equipment0101
    {
        UINT8 type[8];
        UINT8 typeId[8];
    };
    #endif

    struct CharacterList
    {
        UINT16 opcode; // 0x101
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
        char charName[19];
        bool deleted;
        bool nameChange;
        CloakBadge cloakBadge;
    };
    #pragma pack(pop)
}
