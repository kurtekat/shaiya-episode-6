#pragma once
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/Sex.h>
#include <shaiya/include/user/MotionType.h>
#include <shaiya/include/user/PartyType.h>
#include <shaiya/include/user/ShapeType.h>
#include "include/shaiya/common.h"

namespace shaiya
{
    struct CCharacterChat;
    struct CMonster;
    struct SStaticText;

    enum struct CharacterActionType : UINT32
    {
        Idle,
        Move,
        Attack,
        Jump,
        SitDown = 5,
        StandUp,
        Break,
        Cast,
        UseSkill
    };

    enum struct CharacterStatus : UINT32
    {
        None,
        Death,
        Unknown
    };

    #pragma pack(push, 1)
    struct CharacterTitle
    {
        SStaticText* text;
        long pointX;
        int effectDataId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // 00419800 ctor
    struct CCharacter
    {
        PAD(16);
        D3DVECTOR pos;                //0x10
        D3DVECTOR dir;                //0x1C
        D3DVECTOR up;                 //0x28
        ULONG id;                     //0x34
        UINT32 upperModel;            //0x38
        UINT32 handsModel;            //0x3C
        UINT32 lowerModel;            //0x40
        UINT32 bootsModel;            //0x44
        UINT32 faceModel;             //0x48
        UINT32 headModel;             //0x4C
        PAD(92);
        BOOL enableCostume;           //0xAC
        Array<UINT32, 6> costume;     //0xB0
        // 0xC8
        PAD(32);
        MotionType32 motionType1;     //0xE8
        MotionType32 motionType2;     //0xEC
        PAD(8);
        // 0xF8
        CharacterActionType actionType1;
        PAD(16);
        CharArray<21> charName;       //0x10C
        CharArray<51> shapeName;      //0x121
        PAD(4);
        UINT32 health;                //0x158
        UINT32 maxHealth;             //0x15C
        UINT32 mana;                  //0x160
        UINT32 maxMana;               //0x164
        UINT32 stamina;               //0x168
        UINT32 maxStamina;            //0x16C
        D3DVECTOR movePos;            //0x170
        D3DVECTOR moveDir;            //0x17C
        ULONG targetId;               //0x188
        PAD(4);
        BOOL running;                 //0x190
        PAD(4);
        BOOL enableLight;             //0x198
        UINT8 hair;                   //0x19C
        UINT8 face;                   //0x19D
        UINT8 size;                   //0x19E
        Sex sex;                      //0x19F
        Job job;                      //0x1A0
        PAD(7);
        UINT8 helmetType;             //0x1A8
        UINT8 upperType;              //0x1A9
        UINT8 lowerType;              //0x1AA
        UINT8 gloveType;              //0x1AB
        UINT8 bootType;               //0x1AC
        UINT8 weaponType;             //0x1AD
        UINT8 shieldType;             //0x1AE
        UINT8 mantleType;             //0x1AF
        PAD(5);
        UINT8 vehicleType;            //0x1B5
        UINT8 petType;                //0x1B6
        UINT8 costumeType;            //0x1B7
        UINT8 wingsType;              //0x1B8
        UINT8 helmetTypeId;           //0x1B9
        UINT8 upperTypeId;            //0x1BA
        UINT8 lowerTypeId;            //0x1BB
        UINT8 gloveTypeId;            //0x1BC
        UINT8 bootTypeId;             //0x1BD
        UINT8 weaponTypeId;           //0x1BE
        UINT8 shieldTypeId;           //0x1BF
        UINT8 mantleTypeId;           //0x1C0
        PAD(5);
        UINT8 vehicleTypeId;          //0x1C6
        UINT8 petTypeId;              //0x1C7
        UINT8 costumeTypeId;          //0x1C8
        UINT8 wingsTypeId;            //0x1C9
        PAD(18);
        DWORD attackTime;             //0x1DC
        DWORD actionTime;             //0x1E0
        // 0x1E4
        CharacterActionType actionType2;
        bool isEmoteAction;           //0x1E8
        PAD(3);
        ULONG attackTargetId;         //0x1EC
        UINT16 targetDmgHP;           //0x1F0
        UINT16 targetDmgSP;           //0x1F2
        UINT16 targetDmgMP;           //0x1F4
        PAD(6);
        UINT8 attackResult;           //0x1FC
        PAD(135);
        CharacterStatus status;       //0x284
        CCharacterChat* chatBalloon;  //0x288
        // 0x747538 5.0 (seconds)
        float chatBalloonTimer;       //0x28C
        PAD(37);
        UINT8 attackSpeed;            //0x2B5
        UINT8 moveSpeed;              //0x2B6
        Country country;              //0x2B7
        Family family;                //0x2B8
        Grow grow;                    //0x2B9
        PAD(10);
        BOOL visible;                 //0x2C4
        PAD(12);
        bool isAdmin;                 //0x2D4
        PAD(23);
        ShapeType shapeType;          //0x2EC
        PAD(23);
        ULONG killerId;               //0x304
        PartyType partyType;          //0x308
        PAD(3);
        char* guildName;              //0x30C
        ULONG guildId;                //0x310
        SStaticText* charNameText;    //0x314
        long charNamePointX;          //0x318
        SStaticText* guildNameText;   //0x31C
        long guildNamePointX;         //0x320
        SStaticText* myShopMsgText;   //0x324
        PAD(12);
        UINT32 kills;                 //0x334
        BOOL myShopOpen;              //0x338
        CharArray<128> myShopMsg;     //0x33C
        PAD(4);
        UINT8 vehicleSeatCount;       //0x3C0
        UINT8 vehicleModel;           //0x3C1
        PAD(2);
        UINT32 vehicleSpeed;          //0x3C4
        bool isSnowboard;             //0x3C8
        PAD(91);
        BOOL isGuildMaster;           //0x424
        PAD(8);
        CMonster* pet;                //0x430
        CMonster* wings;              //0x434
        PAD(4);
        // 0x43C

        // custom
        CharacterTitle title;         //0x43C

        static void ClearEffects(CCharacter* user);
        static void RemoveEffect(CCharacter* user, int effectDataId, int effectSubId);
        static void RenderEffect(CCharacter* user, int effectDataId, int effectSubId, float delay, D3DVECTOR* pos, D3DVECTOR* dir, D3DVECTOR* up, int unknown);
    };
    #pragma pack(pop)

    //static_assert(sizeof(CCharacter) == 0x43C);
    static_assert(sizeof(CCharacter) == 0x448);
}
