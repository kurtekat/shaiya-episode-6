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
        uint32_t charId;         //0x00
        time32_t createDate;     //0x04
        bool enableRename;       //0x08
        uint8_t slot;            //0x09
        Family family;           //0x0A
        Grow grow;               //0x0B
        uint8_t hair;            //0x0C
        uint8_t face;            //0x0D
        uint8_t size;            //0x0E
        Job job;                 //0x0F
        Sex sex;                 //0x10
        uint16_t level;          //0x11
        uint16_t strength;       //0x13
        uint16_t dexterity;      //0x15
        uint16_t reaction;       //0x17
        uint16_t intelligence;   //0x19
        uint16_t wisdom;         //0x1B
        uint16_t luck;           //0x1D
        uint16_t health;         //0x1F
        uint16_t mana;           //0x21
        uint16_t stamina;        //0x23
        uint16_t mapId;          //0x25
        time32_t deleteDate;     //0x27
        ItemList_EP5 equipment;  //0x2B
        CloakInfo cloakInfo;     //0x3B
        String<21> charName;     //0x41
        // 0x56
    };
    #pragma pack(pop)

    static_assert(sizeof(DBCharacterList_EP5) == 0x56);

    #pragma pack(push, 1)
    struct DBCharacterList_EP6_4
    {
        uint32_t charId;           //0x00
        time32_t createDate;       //0x04
        bool enableRename;         //0x08
        uint8_t slot;              //0x09
        Family family;             //0x0A
        Grow grow;                 //0x0B
        uint8_t hair;              //0x0C
        uint8_t face;              //0x0D
        uint8_t size;              //0x0E
        Job job;                   //0x0F
        Sex sex;                   //0x10
        uint16_t level;            //0x11
        uint16_t strength;         //0x13
        uint16_t dexterity;        //0x15
        uint16_t reaction;         //0x17
        uint16_t intelligence;     //0x19
        uint16_t wisdom;           //0x1B
        uint16_t luck;             //0x1D
        uint16_t health;           //0x1F
        uint16_t mana;             //0x21
        uint16_t stamina;          //0x23
        uint16_t mapId;            //0x25
        time32_t deleteDate;       //0x27
        ItemList_EP6_4 equipment;  //0x2B
        CloakInfo cloakInfo;       //0x4D
        String<21> charName;       //0x53
        // 0x68
    };
    #pragma pack(pop)

    static_assert(sizeof(DBCharacterList_EP6_4) == 0x68);
}
