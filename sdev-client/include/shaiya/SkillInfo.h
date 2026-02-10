#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Attribute.h>
#include <shaiya/include/common/Country.h>

namespace shaiya
{
    enum struct SkillAbilityType : uint8_t
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
        AbilityAddMagicDefense,
        AbilityEvasionRate,
        AbilityRangedEvasionRate,
        AbilityMagicEvasionRate,
        AttackBlinded,
        RangedAttackBlinded,
        Silenced,
        MultiplyExp,
        EternalEndurance,
        PreventItemDrop,
        PreventExpLoss,
        RecallWarehouse,
        WhiteTigerCharm,
        BlueDragonCharm,
        RedPhoenixCharm,
        DoubleWarehouse,
        IncreaseGoldDrop,
        PreventEquipmentDrop,
        ContinuousResurrection,
        BattlefieldRune,
        AbilityAbsorption,
        GoddessCurse,
        EnableEnterDungeon,
        DisableEnterDungeon,
        VitalityStrTraining,
        VitalityRecTraining,
        VitalityIntTraining,
        VitalityWisTraining,
        VitalityDexTraining,
        VitalityLucTraining,
        Frenzied = 70,
        AbilityAddDefensePercentage = 73,
        AbilityAddRangedDefensePercentage,
        AbilityAddMagicResistancePercentage = 78,
        MultiplyQuestExp = 87
    };

    enum struct SkillStatusType : uint8_t
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

    enum struct SkillTargetType : uint8_t
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
    struct SkillAbility
    {
        Array<SkillAbilityType, 10> type;
        Array<uint16_t, 10> value;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct SkillInfo
    {
        PAD(2);
        uint8_t skillLv;          //0x02
        PAD(1);
        char* name;               //0x04
        uint16_t icon;            //0x08
        uint8_t animation;        //0x0A
        PAD(7);
        uint16_t level;           //0x12
        Faction country;          //0x14
        bool fighter;             //0x15
        bool defender;            //0x16
        bool ranger;              //0x17
        bool archer;              //0x18
        bool mage;                //0x19
        bool priest;              //0x1A
        Grow grow;                //0x1B
        uint8_t skillPoints;      //0x1C
        uint8_t typeShow;         //0x1D
        uint8_t typeAttack;       //0x1E
        uint8_t typeEffect;       //0x1F
        uint16_t typeDetail;      //0x20
        bool needOneHandedSword;  //0x22
        bool needTwoHandedSword;  //0x23
        bool needOneHandedAxe;    //0x24
        bool needTwoHandedAxe;    //0x25
        bool needDualWeapon;      //0x26
        bool needSpear;           //0x27
        bool needOneHandedBlunt;  //0x28
        bool needTwoHandedBlunt;  //0x29
        bool needReverseDagger;   //0x2A
        bool needDagger;          //0x2B
        bool needJavelin;         //0x2C
        bool needStaff;           //0x2D
        bool needBow;             //0x2E
        bool needCrossbow;        //0x2F
        bool needKnuckles;        //0x30
        bool needShield;          //0x31
        uint16_t stamina;         //0x32
        uint16_t mana;            //0x34
        uint16_t readyTime;       //0x36
        uint16_t resetTime;       //0x38
        uint8_t range;            //0x3A
        PAD(13);
        uint32_t keepTime;        //0x48
        PAD(6);
        uint32_t damage;          //0x52
        PAD(16);
        SkillAbility abilities;   //0x66
        // 0x84
        PAD(20);
        char* description;        //0x98
        // 0x9C
    };
    #pragma pack(pop)

    static_assert(sizeof(SkillInfo) == 0x9C);
}
