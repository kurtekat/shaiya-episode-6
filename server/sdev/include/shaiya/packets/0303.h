#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/CUser.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct Equipment0303
    {
        UINT8 type;
        UINT8 typeId;
        UINT8 enchantStep;
    };

    struct UserShapeOutgoing
    {
        UINT16 opcode{ 0x303 };
        ULONG charId;
        bool dead;
        bool sitting;
        Country country;
        Family family;
        UINT8 hair;
        UINT8 face;
        UINT8 size;
        Job job;
        Sex sex;
        UINT8 partyType;
        Grow grow;
        UINT32 kills;
        Array<Equipment0303, ITEM_LIST_SIZE> equipment;
        CharName charName;
        CloakBadge cloakBadge;
        GuildName guildName;
    };
    #pragma pack(pop)
}
