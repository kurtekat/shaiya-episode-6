#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    struct CMonster;

    #pragma pack(push, 1)
    enum struct ActionType : UINT32
    {
        None,
        Move,
        Attack,
        Jump,
        SitDown = 5,
        StandUp,
        Break,
        Cast,
        UseSkill
    };

    enum struct Animation : UINT32
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

    enum struct EventType : UINT32
    {
        None,
        Unknown,
        Death,
        Rebirth
    };

    struct GuildName
    {
        Array<char, 32> text;
    };

    struct CCharacter
    {
        PAD(16);
        D3DVECTOR pos;                //0x10
        D3DVECTOR dir;                //0x1C
        D3DVECTOR up;                 //0x28
        CharId id;                    //0x34
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
        Animation ani;                //0xE8
        Animation nextAni;            //0xEC
        PAD(8);
        ActionType actionType;        //0xF8
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
        UINT8 vehicleType;            //0x1B0
        PAD(5);
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
        UINT8 vehicleTypeId;          //0x1C1
        PAD(5);
        UINT8 petTypeId;              //0x1C7
        UINT8 clothesTypeId;          //0x1C8
        UINT8 wingsTypeId;            //0x1C9
        PAD(235);
        UINT8 attackSpeed;            //0x2B5
        UINT8 moveSpeed;              //0x2B6
        Country country;              //0x2B7
        Family family;                //0x2B8
        Grow grow;                    //0x2B9
        PAD(6);
        EventType eventType;          //0x2C0
        BOOL visible;                 //0x2C4
        PAD(12);
        bool isAdmin;                 //0x2D4
        PAD(23);
        ShapeType shapeType;          //0x2EC
        PAD(31);
        GuildName* guildName;         //0x30C
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
