#pragma once
#include <sdev/include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct Equipment0403
    {
        Array<UINT8, ITEM_LIST_SIZE> type;
        Array<UINT8, ITEM_LIST_SIZE> typeId;
    };

    struct Character0403
    {
        CharId id;                //0x00
        ULONG regDate;            //0x04
        bool deleted;             //0x08
        UINT8 slot;               //0x09
        Family family;            //0x0A
        Grow grow;                //0x0B
        UINT8 hair;               //0x0C
        UINT8 face;               //0x0D
        UINT8 size;               //0x0E
        Job job;                  //0x0F
        Sex sex;                  //0x10
        UINT16 level;             //0x11
        UINT16 strength;          //0x13
        UINT16 dexterity;         //0x15
        UINT16 reaction;          //0x17
        UINT16 intelligence;      //0x19
        UINT16 wisdom;            //0x1B
        UINT16 luck;              //0x1D
        UINT16 health;            //0x1F
        UINT16 mana;              //0x21
        UINT16 stamina;           //0x23
        UINT16 mapId;             //0x25
        BOOL nameChange;          //0x27
        Equipment0403 equipment;  //0x2B
        // 6.4: 0x4D, 6.3: 0x4B, 5.4: 0x3B
        CloakBadge cloakBadge;
        // 6.4: 0x53, 6.3: 0x51, 5.4: 0x41
        CharName name;
        #ifdef SHAIYA_EP6_3_COMMON
        PAD(2);
        #endif
        // 6.4, 6.3: 0x68, 5.4: 0x56
    };

    struct CharacterList
    {
        UINT16 opcode{ 0x403 };
        UserId userId;
        bool sendCountry;
        UINT8 characterCount;
        Array<Character0403, 5> characterList;
    };
    #pragma pack(pop)
}
