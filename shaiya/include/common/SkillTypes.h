#pragma once
#include <cstdint>

namespace shaiya
{
    #pragma pack(push, 1)
    struct NeedWeapon
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

    enum struct SkillCharmType : int32_t
    {
        None,
        BlueDragon,
        WhiteTiger,
        RedPhoenix
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
}
