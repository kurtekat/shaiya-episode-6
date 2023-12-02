#pragma once
#include <sdev/include/shaiya/common.h>

namespace shaiya
{
    struct SConnection;

    #pragma pack(push, 1)
    struct Equipment
    {
        Array<UINT8, 8> type;
        Array<UINT8, 8> typeId;
    };

    struct Character
    {
        CharId id;              //0x00
        ULONG regDate;          //0x04
        UINT8 slot;             //0x08
        Family family;          //0x09
        Grow grow;              //0x0A
        UINT8 hair;             //0x0B
        UINT8 face;             //0x0C
        UINT8 size;             //0x0D
        Job job;                //0x0E
        Sex sex;                //0x0F
        UINT16 level;           //0x10
        UINT16 strength;        //0x12
        UINT16 dexterity;       //0x14
        UINT16 reaction;        //0x16
        UINT16 intelligence;    //0x18
        UINT16 wisdom;          //0x1A
        UINT16 luck;            //0x1C
        UINT16 health;          //0x1E
        UINT16 mana;            //0x20
        UINT16 stamina;         //0x22
        UINT16 mapId;           //0x24
        PAD(2);
        BOOL nameChange;        //0x28
        Equipment equipment;    //0x2C
        CloakBadge cloakBadge;  //0x3C
        CharName name;          //0x42
        PAD(1);
        bool deleted;           //0x58
        PAD(3);
        // 0x5C
    };

    struct CUser
    {
        PAD(56);
        UserId userId;                      //0x38
        PAD(36);
        CharId charId;                      //0x60
        PAD(15112);
        Array<Character, 5> characterList;  //0x3B6C
        // 0x3D38
        PAD(17340);
        UINT32 points;                      //0x80F4
        PAD(380);
        ProductCode productCode;            //0x8274
        PAD(3);
        UINT32 itemPrice;                   //0x828C
        PAD(1384);
        SConnection* connection;            //0x87F8
        PAD(92);
        // 0x8858
    };
    #pragma pack(pop)
}
