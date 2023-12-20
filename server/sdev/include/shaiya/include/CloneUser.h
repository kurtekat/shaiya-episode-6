#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/SNode.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CloneItem
    {
        UINT8 type;
        UINT8 typeId;
        UINT8 enchantStep;
    };

    struct CloneUser
    {
        SNode node;               //0x00
        bool dead;                //0x08
        bool sitting;             //0x09
        Country country;          //0x0A
        Family family;            //0x0B
        UINT8 hair;               //0x0C
        UINT8 face;               //0x0D
        UINT8 size;               //0x0E
        Job job;                  //0x0F
        Sex sex;                  //0x10
        UINT8 partyType;          //0x11
        Grow grow;                //0x12
        PAD(1);
        UINT32 kills;             //0x14
        // 0x18
        Array<CloneItem, item_list_size> equipment;
        // 6.4: 0x4B, 6.3: 0x48, 5.4: 0x30
        CharName charName;
        // 6.4: 0x60, 6.3: 0x5D, 5.4: 0x45
        CloakBadge cloakBadge;
        // 6.4: 0x66, 6.3: 0x63, 5.4: 0x4B
        GuildName guildName;
        // 6.4: 0x7F, 6.3: 0x7C, 5.4: 0x64
        UINT8 packetLength;
        #ifdef SHAIYA_EP6_3_COMMON
        PAD(3);
        #endif
        // 6.4, 6.3: 0x80, 5.4: 0x68
    };
    #pragma pack(pop)
}
