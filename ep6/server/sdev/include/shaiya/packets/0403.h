#pragma once
#include <shaiya/common.h>
#include <shaiya/include/CUser.h>

// see CUser::SendCharacterList (0x40AA20)

namespace shaiya
{
    #pragma pack(push, 1)
    #ifdef SHAIYA_EP6
    struct Equipment0403
    {
        UINT8 type[17];
        UINT8 typeId[17];
    };

    struct Character0403
    {
        ULONG charId;             //0x00
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
        CloakBadge cloakBadge;    //0x4D
        char charName[21];        //0x53
        // 0x68
    };
    #else
    struct Equipment0403
    {
        UINT8 type[8];
        UINT8 typeId[8];
    };

    struct Character0403
    {
        ULONG charId;             //0x00
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
        CloakBadge cloakBadge;    //0x3B
        char charName[21];        //0x41
        // 0x56
    };
    #endif

    struct DBCharacterList
    {
        UINT16 opcode;  //0x403
        UINT32 userUid;
        bool sendCountry;
        UINT8 count;
        Character0403 list[5];
    };
    #pragma pack(pop)
}
