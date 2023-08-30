#pragma once
#include <shaiya/common.h>
#include <shaiya/include/CUser.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct Equipment0303
    {
        UINT8 type;
        UINT8 typeId;
        UINT8 enchantStep;
    };

    struct UserShape
    {
        UINT16 opcode; // 0x303
        ULONG charId;
        bool dead;
        bool sitMode;
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
        Equipment0303 equipment[17];
        char charName[21];
        CloakBadge cloakBadge;
        char guildName[25];
    };
    #pragma pack(pop)
}
