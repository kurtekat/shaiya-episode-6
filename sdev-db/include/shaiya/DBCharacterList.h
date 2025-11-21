#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Gems.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/ItemList.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/Sex.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct DBCharacterList_EP5
    {
        uint32_t charId;
        time32_t createDate;
        bool enableRename;
        uint8_t slot;
        Family family;
        Grow grow;
        uint8_t hair;
        uint8_t face;
        uint8_t size;
        Job job;
        Sex sex;
        uint16_t level;
        uint16_t strength;
        uint16_t dexterity;
        uint16_t reaction;
        uint16_t intelligence;
        uint16_t wisdom;
        uint16_t luck;
        uint16_t health;
        uint16_t mana;
        uint16_t stamina;
        uint16_t mapId;
        time32_t deleteDate;
        ItemList<8> equipment;
        CloakInfo cloakInfo;
        String<21> charName;
    };
    #pragma pack(pop)

    static_assert(sizeof(DBCharacterList_EP5) == 0x56);

    #pragma pack(push, 1)
    struct DBCharacterList_EP6_4
    {
        uint32_t charId;
        time32_t createDate;
        bool enableRename;
        uint8_t slot;
        Family family;
        Grow grow;
        uint8_t hair;
        uint8_t face;
        uint8_t size;
        Job job;
        Sex sex;
        uint16_t level;
        uint16_t strength;
        uint16_t dexterity;
        uint16_t reaction;
        uint16_t intelligence;
        uint16_t wisdom;
        uint16_t luck;
        uint16_t health;
        uint16_t mana;
        uint16_t stamina;
        uint16_t mapId;
        time32_t deleteDate;
        ItemList<17> equipment;
        CloakInfo cloakInfo;
        String<21> charName;
    };
    #pragma pack(pop)

    static_assert(sizeof(DBCharacterList_EP6_4) == 0x68);
}
