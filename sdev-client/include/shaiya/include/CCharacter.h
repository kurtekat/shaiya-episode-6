#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/PartyTypes.h>
#include <shaiya/include/common/Sex.h>
#include <shaiya/include/common/UserTypes.h>
#include "include/shaiya/common.h"

namespace shaiya
{
    struct CCharacterChat;
    struct CMonster;
    struct SStaticText;

    enum struct CharacterAction : int32_t
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

    enum struct CharacterStatus : int32_t
    {
        None,
        Death,
        Unknown
    };

    #pragma pack(push, 1)
    // 00419800 ctor
    struct CCharacter
    {
        PAD(16);
        D3DVECTOR pos;                //0x10
        D3DVECTOR dir;                //0x1C
        D3DVECTOR up;                 //0x28
        uint32_t id;                  //0x34
        int32_t upperModel;           //0x38
        int32_t handsModel;           //0x3C
        int32_t lowerModel;           //0x40
        int32_t bootsModel;           //0x44
        int32_t faceModel;            //0x48
        int32_t headModel;            //0x4C
        PAD(92);
        bool32_t enableCostume;       //0xAC
        Array<int32_t, 6> costume;    //0xB0
        // 0xC8
        PAD(32);
        int32_t motionType1;          //0xE8
        int32_t motionType2;          //0xEC
        PAD(8);
        CharacterAction actionType1;  //0xF8
        PAD(16);
        String<21> charName;          //0x10C
        String<51> shapeName;         //0x121
        PAD(4);
        uint32_t health;              //0x158
        uint32_t maxHealth;           //0x15C
        uint32_t mana;                //0x160
        uint32_t maxMana;             //0x164
        uint32_t stamina;             //0x168
        uint32_t maxStamina;          //0x16C
        D3DVECTOR movePos;            //0x170
        D3DVECTOR moveDir;            //0x17C
        uint32_t targetId;            //0x188
        PAD(4);
        bool32_t run;                 //0x190
        PAD(4);
        bool32_t enableLight;         //0x198
        uint8_t hair;                 //0x19C
        uint8_t face;                 //0x19D
        uint8_t size;                 //0x19E
        Sex sex;                      //0x19F
        Job job;                      //0x1A0
        PAD(7);
        uint8_t helmetType;           //0x1A8
        uint8_t upperType;            //0x1A9
        uint8_t lowerType;            //0x1AA
        uint8_t gloveType;            //0x1AB
        uint8_t bootType;             //0x1AC
        uint8_t weaponType;           //0x1AD
        uint8_t shieldType;           //0x1AE
        uint8_t mantleType;           //0x1AF
        PAD(5);
        uint8_t vehicleType;          //0x1B5
        uint8_t petType;              //0x1B6
        uint8_t costumeType;          //0x1B7
        uint8_t wingsType;            //0x1B8
        uint8_t helmetTypeId;         //0x1B9
        uint8_t upperTypeId;          //0x1BA
        uint8_t lowerTypeId;          //0x1BB
        uint8_t gloveTypeId;          //0x1BC
        uint8_t bootTypeId;           //0x1BD
        uint8_t weaponTypeId;         //0x1BE
        uint8_t shieldTypeId;         //0x1BF
        uint8_t mantleTypeId;         //0x1C0
        PAD(5);
        uint8_t vehicleTypeId;        //0x1C6
        uint8_t petTypeId;            //0x1C7
        uint8_t costumeTypeId;        //0x1C8
        uint8_t wingsTypeId;          //0x1C9
        PAD(18);
        uint32_t attackTime;          //0x1DC
        uint32_t actionTime;          //0x1E0
        CharacterAction actionType2;  //0x1E4
        PAD(4);
        uint32_t attackTargetId;      //0x1EC
        uint16_t targetDmgHP;         //0x1F0
        uint16_t targetDmgSP;         //0x1F2
        uint16_t targetDmgMP;         //0x1F4
        PAD(6);
        uint8_t attackResult;         //0x1FC
        PAD(135);
        CharacterStatus status;       //0x284
        CCharacterChat* chatBalloon;  //0x288
        // 0x747538 5.0 (seconds)
        float chatBalloonTimer;       //0x28C
        PAD(37);
        uint8_t attackSpeed;          //0x2B5
        uint8_t moveSpeed;            //0x2B6
        Country country;              //0x2B7
        Family family;                //0x2B8
        Grow grow;                    //0x2B9
        PAD(10);
        bool32_t invisible;           //0x2C4
        PAD(12);
        bool isAdmin;                 //0x2D4
        PAD(23);
        ShapeType shapeType;          //0x2EC
        PAD(23);
        uint32_t killerId;            //0x304
        PartyType partyType;          //0x308
        PAD(3);
        char* guildName;              //0x30C
        uint32_t guildId;             //0x310
        SStaticText* charNameText;    //0x314
        long charNamePointX;          //0x318
        SStaticText* guildNameText;   //0x31C
        long guildNamePointX;         //0x320
        SStaticText* myShopMsgText;   //0x324
        PAD(12);
        uint32_t kills;               //0x334
        bool32_t myShopOpen;          //0x338
        String<128> myShopMessage;    //0x33C
        PAD(4);
        uint8_t vehicleSeatCount;     //0x3C0
        uint8_t vehicleModel;         //0x3C1
        PAD(2);
        int32_t vehicleSpeed;         //0x3C4
        bool isSnowboard;             //0x3C8
        PAD(19);
        D3DXMATRIX vehicleMatrix;     //0x3DC
        // 0x41C
        PAD(8);
        bool32_t isGuildMaster;       //0x424
        PAD(8);
        CMonster* pet;                //0x430
        CMonster* wings;              //0x434
        PAD(4);
        // 0x43C

        static void ClearEffects(CCharacter* user);
        static void RemoveEffect(CCharacter* user, uint effectDataId, uint effectSubId);
        static void RenderEffect(CCharacter* user, uint effectDataId, uint effectSubId, float delay, D3DVECTOR* pos, D3DVECTOR* dir, D3DVECTOR* up, int unknown/*0:9*/);
    };
    #pragma pack(pop)

    static_assert(sizeof(CCharacter) == 0x43C);
}
