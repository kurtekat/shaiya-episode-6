#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    struct CMonster;

    typedef Array<UINT32, 6> Clothes;
    typedef Array<char, 51> ShapeName;

    enum struct CharacterAnimation : UINT32
    {
        None,
        Walk,
        Run,
        WalkBack,
        WalkLeft,
        WalkRight,
        Wade,
        Swim,
        Jump,
        Death,
        SitDown,
        StandUp,
        Break,
        JumpBack,
        JumpLeft,
        JumpRight,
        Idle1,
        Idle2,
        Climb,
        SelectionScreen,
        VehicleRunMode,
        Vehicle,
        Snowboard,
        TwoHandedAtkMode,
        TwoHandedAttack1,
        TwoHandedAttack2,
        TwoHandedAttack3,
        TwoHandedAttack4,
        TwoHandedDamage,
        TwoHandedRunMode,
        BowAtkMode,
        BowAttack,
        BowDamage,
        BowRunMode,
        OneHandedAtkMode,
        OneHandedAttack1,
        OneHandedAttack2,
        OneHandedAttack3,
        OneHandedAttack4,
        OneHandedDamage,
        OneHandedRunMode,
        DualWieldAtkMode,
        DualWieldAttack1,
        DualWieldAttack2,
        DualWieldAttack3,
        DualWieldAttack4,
        DualWieldDamage,
        DualWieldRunMode,
        SpearAtkMode,
        SpearAttack1,
        SpearAttack2,
        SpearAttack3,
        SpearAttack4,
        SpearDamage,
        SpearRunMode,
        JavelinAtkMode,
        JavelinAttack,
        JavelinDamage,
        JavelinRunMode,
        StaffAtkMode,
        StaffAttack1,
        StaffAttack2,
        StaffDamage,
        StaffRunMode,
        ReverseAtkMode,
        ReverseAttack1,
        ReverseAttack2,
        ReverseAttack3,
        ReverseAttack4,
        ReverseDamage,
        ReverseRunMode,
        KnuckleAtkMode,
        KnuckleAttack1,
        KnuckleAttack2,
        KnuckleAttack3,
        KnuckleAttack4,
        KnuckleDamage,
        KnuckleRunMode,
        DaggerAtkMode,
        DaggerAttack1,
        DaggerAttack2,
        DaggerAttack3,
        DaggerAttack4,
        DaggerDamage,
        DaggerRunMode,
        Cast85,
        Cast86,
        UseSkill87,
        Cast88,
        Cast89,
        UseSkill90,
        Cast91,
        Cast92,
        UseSkill93,
        Cast94,
        Cast95,
        UseSkill96,
        Cast97,
        Cast98,
        UseSkill99,
        Skill100,
        Skill101,
        Skill102,
        Skill103,
        Skill104,
        Skill105,
        Skill106,
        Skill107,
        Skill108,
        Skill109,
        Skill110,
        Beg = 116,
        Victory,
        Laugh,
        Love,
        Greet,
        Clap,
        Defeat,
        Start,
        Insult,
        Provoke
    };

    enum struct CharacterAction : UINT32
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
        BOOL enableClothes;           //0xAC
        Clothes clothes;              //0xB0
        // 0xC8
        PAD(32);
        // 0xE8
        CharacterAnimation animation;
        // 0xEC
        CharacterAnimation animation2;
        PAD(8);
        CharacterAction action;       //0xF8
        PAD(16);
        CharName charName;            //0x10C
        ShapeName shapeName;          //0x121
        PAD(4);
        UINT32 health;                //0x158
        UINT32 maxHealth;             //0x15C
        UINT32 mana;                  //0x160
        UINT32 maxMana;               //0x164
        UINT32 stamina;               //0x168
        UINT32 maxStamina;            //0x16C
        D3DVECTOR nextPos;            //0x170
        D3DVECTOR nextDir;            //0x17C
        ULONG targetId;               //0x188
        PAD(4);
        BOOL running;                 //0x190
        PAD(8);
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
        UINT8 clothesType;            //0x1B7
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
        UINT8 clothesTypeId;          //0x1C8
        UINT8 wingsTypeId;            //0x1C9
        PAD(18);
        DWORD attackTime;             //0x1DC
        DWORD actionTime;             //0x1E0
        CharacterAction action2;      //0x1E4
        bool isEmoteAction;           //0x1E8
        PAD(3);
        ULONG attackTargetId;         //0x1EC
        UINT16 targetDmgHP;           //0x1F0
        UINT16 targetDmgSP;           //0x1F2
        UINT16 targetDmgMP;           //0x1F4
        PAD(6);
        UINT8 attackResult;           //0x1FC
        PAD(184);
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
        PAD(31);
        char* guildName;              //0x30C
        ULONG guildId;                //0x310
        PAD(32);
        UINT32 kills;                 //0x334
        PAD(136);
        UINT8 vehicleSeats;           //0x3C0
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
    };
    #pragma pack(pop)
}
