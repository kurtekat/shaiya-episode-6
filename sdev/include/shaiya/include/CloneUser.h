#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/ItemTypes.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/PartyTypes.h>
#include <shaiya/include/common/Sex.h>
#include <shaiya/include/common/UserTypes.h>
#include "include/shaiya/include/SNode.h"

namespace shaiya
{
    #pragma pack(push, 1)
    // 8 items (5.4, 6.0)
    struct CloneUser_EP5
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
        PartyType partyType;      //0x11
        Grow grow;                //0x12
        PAD(1);
        UINT32 kills;             //0x14
        Equipment<8> equipment;   //0x18
        CharName charName;        //0x30
        CloakBadge cloakBadge;    //0x45
        CharArray<25> guildName;  //0x4B
        UINT8 packetLength;       //0x64
        PAD(3);
        // 0x68
    };
    #pragma pack(pop)

    static_assert(sizeof(CloneUser_EP5) == 0x68);

    #pragma pack(push, 1)
    // 17 items (6.4)
    struct CloneUser_EP6_4
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
        PartyType partyType;      //0x11
        Grow grow;                //0x12
        PAD(1);
        UINT32 kills;             //0x14
        Equipment<17> equipment;  //0x18
        CharName charName;        //0x4B
        CloakBadge cloakBadge;    //0x60
        CharArray<25> guildName;  //0x66
        UINT8 packetLength;       //0x7F
        // 0x80
    };
    #pragma pack(pop)

    static_assert(sizeof(CloneUser_EP6_4) == 0x80);
    using CloneUser = CloneUser_EP6_4;
}
