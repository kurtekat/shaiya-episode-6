#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Gems.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/ItemList.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/PartyTypes.h>
#include <shaiya/include/common/Sex.h>
#include <shaiya/include/common/UserTypes.h>
#include <shaiya/include/network/game/GetInfoItemType.h>
#include "SNode.h"

namespace shaiya
{
    #pragma pack(push, 1)
    // 8 items (5.4, 6.0)
    struct CloneUser_EP5 : SNode
    {
        bool dead;                //0x08
        uint8_t motion;           //0x09
        Country country;          //0x0A
        Family family;            //0x0B
        uint8_t hair;             //0x0C
        uint8_t face;             //0x0D
        uint8_t size;             //0x0E
        Job job;                  //0x0F
        Sex sex;                  //0x10
        PartyType partyType;      //0x11
        Grow grow;                //0x12
        PAD(1);
        uint32_t kills;           //0x14
        // 0x18
        Array<GetInfoItemType, 8> equipment;
        String<21> charName;      //0x30
        CloakInfo cloakInfo;      //0x45
        String<25> guildName;     //0x4B
        uint8_t packetLength;     //0x64
        PAD(3);
        // 0x68
    };
    #pragma pack(pop)

    static_assert(sizeof(CloneUser_EP5) == 0x68);

    #pragma pack(push, 1)
    // 17 items (6.4)
    struct CloneUser : SNode
    {
        bool dead;                //0x08
        uint8_t motion;           //0x09
        Country country;          //0x0A
        Family family;            //0x0B
        uint8_t hair;             //0x0C
        uint8_t face;             //0x0D
        uint8_t size;             //0x0E
        Job job;                  //0x0F
        Sex sex;                  //0x10
        PartyType partyType;      //0x11
        Grow grow;                //0x12
        PAD(1);
        uint32_t kills;           //0x14
        // 0x18
        Array<GetInfoItemType, 17> equipment;
        String<21> charName;      //0x4B
        CloakInfo cloakInfo;      //0x60
        String<25> guildName;     //0x66
        uint8_t packetLength;     //0x7F
        // 0x80
    };
    #pragma pack(pop)

    static_assert(sizeof(CloneUser) == 0x80);
}
