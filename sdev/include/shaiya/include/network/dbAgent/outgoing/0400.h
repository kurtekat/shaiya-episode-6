#pragma once
#include <strsafe.h>
#include <shaiya/include/common.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/Gems.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/Sex.h>

namespace shaiya
{
    enum struct DBAgentCharCreateResult : UINT8
    {
        Success,
        Failure,
        NullUser = 3
    };

    #pragma pack(push, 1)
    // 8 items (5.4, 6.0)
    struct Character0403
    {
        ULONG id;                 //0x00
        ULONG regDate;            //0x04
        bool nameChange;          //0x08
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
        ULONG deleteDate;         //0x27
        Array<UINT8, 8> type;     //0x2B
        Array<UINT8, 8> typeId;   //0x33
        CloakBadge cloakBadge;    //0x3B
        CharArray<21> charName;   //0x41
        // 0x56
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentCharListOutgoing
    {
        UINT16 opcode{ 0x403 };
        ULONG userId;
        bool sendCountry;
        UINT8 characterCount;
        Array<Character0403, 5> characterList;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // 17 items (6.4 PT)
    struct Character0403v2
    {
        ULONG id;                 //0x00
        ULONG regDate;            //0x04
        bool nameChange;          //0x08
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
        ULONG deleteDate;         //0x27
        Array<UINT8, 17> type;    //0x2B
        Array<UINT8, 17> typeId;  //0x3C
        CloakBadge cloakBadge;    //0x4D
        CharArray<21> charName;   //0x53
        // 0x68
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentCharListOutgoing2
    {
        UINT16 opcode{ 0x403 };
        ULONG userId;
        bool sendCountry;
        UINT8 characterCount;
        Array<Character0403v2, 5> characterList;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentCharCreateResultOutgoing
    {
        UINT16 opcode{ 0x404 };
        ULONG userId;
        DBAgentCharCreateResult result;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentCharNameChangeOutgoing
    {
        UINT16 opcode{ 0x409 };
        ULONG userId;
        bool success;
        ULONG charId;
        CharArray<21> oldCharName;
        CharArray<21> newCharName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentCharDeleteOutgoing
    {
        UINT16 opcode{ 0x40A };
        ULONG userId;
        ULONG charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentCharRestoreOutgoing
    {
        UINT16 opcode{ 0x40B };
        ULONG userId;
        ULONG charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // custom
    struct DBAgentCharNameAvailableOutgoing
    {
        UINT16 opcode{ 0x40D };
        ULONG userId;
        bool available;
    };
    #pragma pack(pop)
}
