#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    typedef Array<char, 32> SkillName;

    enum struct SkillAbilityType : UINT8
    {
        MaxHealth = 1,
        MaxMana,
        MaxStamina,
        AbilityStrength,
        AbilityReaction,
        AbilityIntelligence,
        AbilityWisdom,
        AbilityDexterity,
        AbilityLuck,
        AddHpRecovery,
        AddSpRecovery,
        AddMpRecovery,
        DecreaseSpCostPercentage,
        DecreaseMpCostPercentage,
        AbilityAttackRange,
        AbilityAttackSpeed,
        AbilityMoveSpeed,
        AbilityCriticalHitRate,
        DecreaseSkillResetTime,
        AbilityHitRate,
        AbilityRangedHitRate,
        AbilityMagicHitRate,
        AbilityAttackPower,
        AbilityRangedAttackPower,
        AbilityMagicPower,
        AbilityAddDefense,
        AbilityAddRangedDefense,
        AbilityMagicResistance,
        AbilityEvasionRate,
        AbilityRangedEvasionRate,
        AbilityMagicEvasionRate,
        AttackBlinded,
        RangedAttackBlinded,
        Silenced,
        IncreaseExpRate,
        EternalEndurance,
        PreventItemDrop,
        PreventExpLoss,
        RecallWarehouse,
        WhiteTigerCharm,
        BlueDragonCharm,
        RedPhoenixCharm,
        DoubleWarehouse,
        IncreaseGoldRate,
        PreventEquipmentDrop,
        ContinuousResurrection,
        BattlefieldRune,
        AbilityAbsorption,
        BaseStatus,
        Frenzied = 70
    };

    #pragma pack(push, 1)
    struct SkillAbility
    {
        SkillAbilityType type;
        PAD(1);
        UINT16 value;
    };
    #pragma pack(pop)

    enum struct SkillStateType : UINT8
    {
        None,
        Sleep,
        Unconscious,
        Silence,
        Darkness,
        Pause,
        Slow,
        Dying,
        Death,
        Poison,
        Illness,
        Delusion,
        Doom,
        Fear,
        Dull,
        Misfortune
    };

    enum struct SkillTargetType : UINT8
    {
        None,
        Trap,
        Caster,
        Target,
        AlliesNearCaster,
        Allies,
        EnemiesNearCaster,
        EnemiesNearTarget
    };

    #pragma pack(push, 1)
    struct SkillWeapon
    {
        bool oneHandedSword;
        bool twoHandedSword;
        bool oneHandedAxe;
        bool twoHandedAxe;
        bool dualWeapon;
        bool spear;
        bool oneHandedBlunt;
        bool twoHandedBlunt;
        bool reverseDagger;
        bool dagger;
        bool javelin;
        bool staff;
        bool bow;
        bool crossbow;
        bool knuckles;
        bool shield;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct SkillInfo
    {
        UINT16 skillId;           //0x00
        UINT8 skillLv;            //0x02
        SkillName skillName;      //0x03
        PAD(1);
        UINT16 level;             //0x24
        UINT8 country;            //0x26
        ReqJob job;               //0x27
        Grow grow;                //0x2D
        UINT8 skillPoint;         //0x2E
        UINT8 typeShow;           //0x2F
        UINT8 typeAttack;         //0x30
        UINT8 typeEffect;         //0x31
        UINT16 typeDetail;        //0x32
        SkillWeapon needWeapon;   //0x34
        UINT16 stamina;           //0x44
        UINT16 mana;              //0x46
        UINT16 readyTime;         //0x48
        UINT16 resetTime;         //0x4A
        UINT8 attackRange;        //0x4C
        SkillStateType stateType; //0x4D
        Attribute attribute;      //0x4E
        PAD(1);
        bool disable;             //0x50
        PAD(1);
        UINT16 prevSkillId;       //0x52
        UINT8 successType;        //0x54
        UINT8 successValue;       //0x55
        // 0x56
        SkillTargetType targetType;
        UINT8 applyRange;         //0x57
        UINT8 multiAttack;        //0x58
        PAD(3);
        ULONG keepTime;           //0x5C
        UINT8 weapon1;            //0x60
        UINT8 weapon2;            //0x61
        UINT8 weaponValue;        //0x62
        UINT8 bag;                //0x63
        UINT16 aggro;             //0x64
        UINT16 damageType;        //0x66
        UINT16 damageHealth;      //0x68
        UINT16 damageStamina;     //0x6A
        UINT16 damageMana;        //0x6C
        UINT8 timeDmgType;        //0x6E
        PAD(1);
        UINT16 timeDmgHealth;     //0x70
        UINT16 timeDmgStamina;    //0x72
        UINT16 timeDmgMana;       //0x74
        UINT16 addDmgHealth;      //0x76
        UINT16 addDmgStamina;     //0x78
        UINT16 addDmgMana;        //0x7A
        // 0x7C
        Array<SkillAbility, 3> ability;
        UINT16 healHealth;        //0x88
        UINT16 healStamina;       //0x8A
        UINT16 healMana;          //0x8C
        UINT16 timeHealHealth;    //0x8E
        UINT16 timeHealStamina;   //0x90
        UINT16 timeHealMana;      //0x92
        UINT8 defenseType;        //0x94
        UINT8 defenseValue;       //0x95 
        UINT8 limitHealth;        //0x96
        UINT8 fixRange;           //0x97
        UINT16 shapeType;         //0x98
        UINT16 shapeMobId;        //0x9A
        PAD(8);
        // 0xA4
    };
    #pragma pack(pop)
}
