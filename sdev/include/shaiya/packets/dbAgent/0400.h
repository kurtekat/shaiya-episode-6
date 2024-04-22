#pragma once
#include <sdev/include/shaiya/common.h>

// CUser::PacketUserChar

namespace shaiya
{
    enum struct UserCharCreateResult : UINT8
    {
        Success,
        Failure,
        NullUser = 3
    };

    #pragma pack(push, 1)
    struct Equipment0403
    {
#ifdef SHAIYA_EP6_4_PT
        Array<UINT8, 17> type;
        Array<UINT8, 17> typeId;
#else
        Array<UINT8, 8> type;
        Array<UINT8, 8> typeId;
#endif
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct Character0403
    {
        CharId id;                //0x00
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
        Equipment0403 equipment;  //0x2B
        // 6.4: 0x4D, 5.4: 0x3B
        CloakBadge cloakBadge;
        // 6.4: 0x53, 5.4: 0x41
        CharName charName;
        // 6.4: 0x68, 5.4: 0x56
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserCharListOutgoing
    {
        UINT16 opcode{ 0x403 };
        UserId userId;
        bool sendCountry;
        UINT8 characterCount;
        Array<Character0403, 5> characterList;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserCharCreateResultOutgoing
    {
        UINT16 opcode{ 0x404 };
        UserId userId;
        UserCharCreateResult result;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserCharDeleteIncoming
    {
        UINT16 opcode{ 0x40A };
        UserId userId;
        ULONG charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserCharDeleteOutgoing
    {
        UINT16 opcode{ 0x40A };
        UserId userId;
        ULONG charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserCharRestoreIncoming
    {
        UINT16 opcode{ 0x40B };
        UserId userId;
        ULONG charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserCharRestoreOutgoing
    {
        UINT16 opcode{ 0x40B };
        UserId userId;
        ULONG charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // custom
    struct UserCharNameAvailableIncoming
    {
        UINT16 opcode{ 0x40D };
        UserId userId;
        Array<char, 19> name;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // custom
    struct UserCharNameAvailableOutgoing
    {
        UINT16 opcode{ 0x40D };
        UserId userId;
        bool available;
    };
    #pragma pack(pop)
}
