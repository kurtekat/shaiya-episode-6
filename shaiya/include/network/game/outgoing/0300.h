#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Gems.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/PartyType.h>
#include <shaiya/include/common/Sex.h>
#include <shaiya/include/network/game/GetInfoItemUnit.h>
#include <shaiya/include/network/game/GetInfoItemType.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_USER_GETHP
    struct GameGetInfoUserHealthOutgoing
    {
        uint16_t opcode{ 0x302 };
        uint32_t objectId;
        uint32_t maxHealth;
        uint32_t health;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_USER_GETSHAPE
    struct GameGetInfoUserShapeOutgoing_EP5
    {
        uint16_t opcode{ 0x303 };
        uint32_t objectId;
        bool dead;
        uint8_t motion;
        Country country;
        Family family;
        uint8_t hair;
        uint8_t face;
        uint8_t size;
        Job job;
        Sex sex;
        PartyType partyType;
        Grow grow;
        uint32_t kills;
        Array<GetInfoItemType, 8> equipment;
        String<21> charName;
        CloakInfo cloakInfo;
        String<25> guildName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_USER_GETSHAPE
    struct GameGetInfoUserShapeOutgoing_EP6_4
    {
        uint16_t opcode{ 0x303 };
        uint32_t objectId;
        bool dead;
        uint8_t motion;
        Country country;
        Family family;
        uint8_t hair;
        uint8_t face;
        uint8_t size;
        Job job;
        Sex sex;
        PartyType partyType;
        Grow grow;
        uint32_t kills;
        Array<GetInfoItemType, 17> equipment;
        String<21> charName;
        CloakInfo cloakInfo;
        String<25> guildName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_MOB_GETHP
    struct GameGetInfoMobHealthOutgoing
    {
        uint16_t opcode{ 0x305 };
        uint32_t objectId;
        uint32_t health;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_USER_ITEMS
    struct GameGetInfoUserItemsOutgoing_EP5
    {
        uint16_t opcode{ 0x307 };
        uint8_t itemCount;
        Array<GetInfoItemUnit_EP5, 13> itemList;

        constexpr static int baseLength = 3;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_USER_ITEMS
    struct GameGetInfoUserItemsOutgoing_EP6_4
    {
        uint16_t opcode{ 0x307 };
        uint8_t itemCount;
        Array<GetInfoItemUnit_EP5, 17> itemList;

        constexpr static int baseLength = 3;
    };
    #pragma pack(pop)
}
