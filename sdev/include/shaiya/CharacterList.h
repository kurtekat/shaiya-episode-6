#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Gems.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/ItemList.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/Sex.h>
#include <shaiya/include/common/UserTypes.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // 8 items (5.4, 6.0)
    struct CharacterList_EP5
    {
        uint32_t charId;
        time32_t createDate;
        uint16_t level;
        Family family;
        Grow grow;
        uint8_t hair;
        uint8_t face;
        uint8_t size;
        Job job;
        Sex sex;
        uint16_t mapId;
        uint16_t strength;
        uint16_t dexterity;
        uint16_t reaction;
        uint16_t intelligence;
        uint16_t wisdom;
        uint16_t luck;
        uint16_t health;
        uint16_t mana;
        uint16_t stamina;
        ItemList<8> equipment;
        String<19> charName;
        bool deleted;
        bool enableRename;
        CloakInfo cloakInfo;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // 17 items (6.4)
    struct CharacterList_EP6_4
    {
        uint32_t charId;
        time32_t createDate;
        uint16_t level;
        Family family;
        Grow grow;
        uint8_t hair;
        uint8_t face;
        uint8_t size;
        Job job;
        Sex sex;
        uint16_t mapId;
        uint16_t strength;
        uint16_t dexterity;
        uint16_t reaction;
        uint16_t intelligence;
        uint16_t wisdom;
        uint16_t luck;
        uint16_t health;
        uint16_t mana;
        uint16_t stamina;
        ItemList<17> equipment;
        String<19> charName;
        bool deleted;
        bool enableRename;
        CloakInfo cloakInfo;
    };
    #pragma pack(pop)
}
