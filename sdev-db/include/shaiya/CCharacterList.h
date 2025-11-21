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
    struct CCharacterList
    {
        uint32_t charId;        //0x00
        time32_t createDate;    //0x04
        uint8_t slot;           //0x08
        Family family;          //0x09
        Grow grow;              //0x0A
        uint8_t hair;           //0x0B
        uint8_t face;           //0x0C
        uint8_t size;           //0x0D
        Job job;                //0x0E
        Sex sex;                //0x0F
        uint16_t level;         //0x10
        uint16_t strength;      //0x12
        uint16_t dexterity;     //0x14
        uint16_t reaction;      //0x16
        uint16_t intelligence;  //0x18
        uint16_t wisdom;        //0x1A
        uint16_t luck;          //0x1C
        uint16_t health;        //0x1E
        uint16_t mana;          //0x20
        uint16_t stamina;       //0x22
        uint16_t mapId;         //0x24
        PAD(2);
        time32_t deleteDate;    //0x28
        // 0x2C
        ItemList<8> equipment;
        CloakInfo cloakInfo;    //0x3C
        String<21> charName;    //0x42
        PAD(1);
        bool32_t enableRename;  //0x58
        // 0x5C
    };
    #pragma pack(pop)

    static_assert(sizeof(CCharacterList) == 0x5C);
}
