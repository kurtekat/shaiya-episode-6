#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    static Address g_GameData = 0x587C68;
    // item effect 59 (EP5 itemId 100169)
    static Address g_ItemSpecialMoveWar = 0x56E668;

    typedef Array<char, 32> ItemName;
    typedef Array<char, 32> MobName;
    typedef Array<char, 51> ProductName;
    typedef Array<char, 32> SkillName;

    struct CGameData
    {
        enum struct Attribute : UINT8
        {
            None,
            Fire,
            Water,
            Earth,
            Wind,
            Fire2,
            Water2,
            Earth2,
            Wind2
        };

        enum ItemCooldown
        {
            Zero = 0,      // 0x581D84
            One = 15000,   // 0x581D88
            Two = 20000,   // 0x581D8C
            Three = 25000, // 0x581D90
            Four = 30000,  // 0x581D94
            Five = 60000,  // 0x581D98
            Six = 120000,  // 0x581D9C
            Seven = 0,     // 0x581DA0
            Eight = 0,     // 0x581DA4
            Nine = 0,      // 0x581DA8
            Ten = 600000,  // 0x581DAC
            Eleven = 2000  // 0x581DB0
        };

        enum struct ItemEffect : UINT8
        {
            HypnosisCure = 1,
            StunCure,
            SilenceCure,
            DarknessCure,
            StopCure,
            SlowCure,
            ProtectedFaint,
            ProtectedDeath,
            VenomCure,
            DiseaseCure,
            DisorderCure,
            ArcanePotion = 17,
            CurePotion,
            DispelPotion,
            AbolishingPotion,
            BlessingPotion,
            HolyPotion,
            PerfectCure = 26,
            GoddessBlessing = 30,
            PartyMemberSummon,
            PartyMemberMoveTo,
            SkillReset,
            StatReset,
            WarehouseRecall,
            LinkingHammer,
            Resurrection,
            MessageToServer,
            Teleportation,
            RepairHammer,
            TargetResurrect,
            ItemCreate,
            IncreaseFame,
            AppearanceChange,
            SexChange,
            Firework,
            CapitalRecall,
            BootleggeryRecall,
            ArenaRecall,
            ExpRemoval,
            NameChange,
            Etin1,
            Etin10,
            Etin100,
            Etin1000,
            GuildHouseRecall,
            LuckyCharm,
            ExtractionHammer,
            MoveWar,
            ItemCompose = 62,
            Promotion,
            EquipMale,
            EquipFemale,
            PerfectLinkingHammer = 69,
            MobGen = 73,
            CrowleyEssence = 85,
            ItemComposeStr,
            ItemComposeDex,
            ItemComposeInt,
            ItemComposeWis,
            ItemComposeRec,
            ItemComposeLuc,
            CrowleyLiquid,
            ItemRemakeStr,
            ItemRemakeDex,
            ItemRemakeInt,
            ItemRemakeWis,
            ItemRemakeRec,
            ItemRemakeLuc,
            ChaoticSquare,
            DungeonMap,
            CraftingHammer = 102,
            SafetyEnchant,
            TownTeleportScroll,
            EnchantEnhancer = 107,
            Dye = 110,
            HaloReactor,
            Spellbook,
            EternalContinuousResurrect,
            EternalPreventItemDrop,
            EternalPreventExpDrop,
            TyrosStone,
            AbsoluteRecreationRune,
            NpcRecall = 200,
            Item500 = 210
        };

        enum struct ItemMarketType : UINT8
        {
            TwoHandedWeapon = 1,
            OneHandedWeapon,
            DualWeapon,
            Spear,
            HeavyWeapon,
            Knuckles,
            Dagger,
            Staff,
            Bow,
            Projectile,
            Helmet,
            UpperArmor,
            LowerArmor,
            Gloves,
            Shoes,
            Cloak,
            Shield,
            Necklace,
            #ifdef SHAIYA_EP6_4_PT
            Vehicle,
            #endif
            Ring,
            Bracelet,
            Lapis,
            Lapisian,
            Other,
            Mount,
            HighQuality
        };

        enum struct ItemRealType : UINT32
        {
            OneHandedSword = 1,
            TwoHandedSword,
            OneHandedAxe,
            TwoHandedAxe,
            DualWeapon,
            Spear,
            OneHandedBlunt,
            TwoHandedBlunt,
            ReverseDagger,
            Dagger,
            Javelin,
            Staff,
            Bow,
            Crossbow,
            Knuckles,
            Helmet,
            UpperArmor,
            LowerArmor,
            Shield,
            Gloves,
            Shoes,
            Ring,
            Necklace,
            Cloak,
            Bracelet,
            Teleportation,
            Quest,
            Gem = 30,
            Vehicle = 42,
            Etin,
        };

        enum struct ItemType : UINT8
        {
            OneHandedSword = 1,
            TwoHandedSword,
            OneHandedAxe,
            TwoHandedAxe,
            DualWield,
            Spear,
            OneHandedBlunt,
            TwoHandedBlunt,
            ReverseDagger,
            Dagger,
            Javelin,
            Staff,
            Bow,
            Crossbow,
            Knuckles,
            LightHelmet,
            LightUpperArmor,
            LightLowerArmor,
            LightShield,
            LightGloves,
            LightShoes,
            Ring,
            Necklace,
            LightCloak,
            Consumable25,
            Gold,
            Quest27,
            Quest28,
            Quest29,
            Gem,
            FuryHelmet,
            FuryUpperArmor,
            FuryLowerArmor,
            Unknown34,
            FuryGloves,
            FuryShoes,
            Ring2,
            Consumable38,
            FuryCloak,
            Bracelet,
            Consumable41,
            Vehicle,
            Etin,
            Consumable44,
            OneHandedSword2,
            TwoHandedSword2,
            OneHandedAxe2,
            TwoHandedAxe2,
            DualWield2,
            DualWield3,
            Spear2,
            Spear3,
            OneHandedBlunt2,
            OneHandedBlunt3,
            TwoHandedBlunt2,
            TwoHandedBlunt3,
            ReverseDagger2,
            Dagger2,
            Javelin2,
            Staff2,
            Staff3,
            Bow2,
            Bow3,
            Crossbow2,
            Knuckles2,
            Unknown66,
            LightUpperArmor2,
            LightLowerArmor2,
            LightShield2,
            LightGloves2,
            LightBoots2,
            LightHelmet3,
            LightUpperArmor3,
            LightLowerArmor3,
            Unknown75,
            LightGloves3,
            LightShoes3,
            Unknown78,
            Unknown79,
            Unknown80,
            Unknown81,
            FuryUpperArmor2,
            FuryLowerArmor2,
            FuryShield2,
            FuryGloves2,
            FuryShoes2,
            FuryHelmet3,
            FuryUpperArmor3,
            FuryLowerArmor3,
            Unknown90,
            FuryGloves3,
            FuryShoes3,
            Unknown93,
            GoldBar,
            Lapisia,
            Necklace2,
            Bracelet2,
            Unknown98,
            Quest99,
            Special100,
            Special101,
            Special102,
            Pet = 120,
            Wings,
            Costume = 150
        };

        enum struct ItemPerfectLapisianType : UINT8
        {
            Weapon,
            Armor
        };

        enum struct ItemReqOg : UINT8
        {
            Tradable,
            AccountBound,
            CharacterBound
        };

        struct ItemInfo
        {
            UINT32 itemId;           //0x00
            ItemName itemName;       //0x04
            UINT8 type;              //0x24
            UINT8 typeId;            //0x25
            Race country;            //0x26
            bool attackFighter;      //0x27
            bool defenseFighter;     //0x28
            bool patrolRogue;        //0x29
            bool shootRogue;         //0x2A
            bool attackMage;         //0x2B
            bool defenseMage;        //0x2C
            PAD(1);
            UINT16 level;            //0x2E
            Grow grow;               //0x30
            ItemReqOg reqOg;         //0x31
            UINT8 reqIg;             //0x32
            PAD(1);
            UINT16 reqVg;            //0x34
            UINT16 reqStr;           //0x36
            UINT16 reqDex;           //0x38
            // rate = value / 100
            UINT16 reqRec;           //0x3A
            UINT16 reqInt;           //0x3C
            UINT16 reqWis;           //0x3E
            UINT16 reqLuc;           //0x40
            UINT16 range;            //0x42
            UINT8 attackTime;        //0x44
            Attribute attribute;     //0x45
            ItemEffect effect;       //0x46
            UINT8 slotCount;         //0x47
            UINT8 speed;             //0x48
            UINT8 absorption;        //0x49
            UINT8 composeCount;      //0x4A
            UINT8 count;             //0x4B
            UINT16 maxQuality;       //0x4C
            UINT16 midQuality;       //0x4E
            UINT16 lowQuality;       //0x50
            UINT16 maxAtkPower;      //0x52
            UINT16 maxAtkPowerMidQ;  //0x54
            UINT16 maxAtkPowerLowQ;  //0x56
            UINT16 minAtkPower;      //0x58
            UINT16 minAtkPowerMidQ;  //0x5A
            UINT16 minAtkPowerLowQ;  //0x5C
            UINT16 defense;          //0x5E
            UINT16 defenseMidQ;      //0x60
            UINT16 defenseLowQ;      //0x62
            UINT16 resistance;       //0x64
            UINT16 resistanceMidQ;   //0x66
            UINT16 resistanceLowQ;   //0x68
            UINT16 health;           //0x6A
            UINT16 stamina;          //0x6C
            UINT16 mana;             //0x6E
            UINT16 strength;         //0x70
            UINT16 dexterity;        //0x72
            UINT16 reaction;         //0x74
            UINT16 intelligence;     //0x76
            UINT16 wisdom;           //0x78
            UINT16 luck;             //0x7A
            UINT32 dropGrade;        //0x7C
            UINT32 buy;              //0x80
            UINT32 sell;             //0x84
            PAD(24);
            ItemRealType realType;      //0xA0
            ItemMarketType marketType;  //0xA4
            PAD(3);
            // 0xA8
        };

        struct KillCountStatus
        {
            UINT32 index;              //0x00
            UINT32 killCount;          //0x04
            UINT32 grade;              //0x08
            PAD(4);
            UINT32 health;             //0x10
            UINT32 stamina;            //0x14
            UINT32 mana;               //0x18
            UINT32 strength;           //0x1C
            UINT32 reaction;           //0x20
            UINT32 intelligence;       //0x24
            UINT32 wisdom;             //0x28
            UINT32 dexterity;          //0x2C
            UINT32 luck;               //0x30
            UINT32 sitHpRecovery;      //0x34
            UINT32 sitSpRecovery;      //0x38
            UINT32 sitMpRecovery;      //0x3C
            UINT32 combatHpRecovery;   //0x40
            UINT32 combatSpRecovery;   //0x44
            UINT32 combatMpRecovery;   //0x48
            UINT32 criticalHitRate;    //0x4C
            UINT32 hitRate;            //0x50
            UINT32 defense;            //0x54
            UINT32 rangedDefense;      //0x58
            UINT32 magicResistance;    //0x5C
            UINT32 evasionRate;        //0x60
            UINT32 rangedEvasionRate;  //0x64
            UINT32 magicEvasionRate;   //0x68
            UINT32 linkSuccessRate;    //0x6C
            UINT32 expLossRate;        //0x70
            UINT32 repairCost;         //0x74
            UINT32 itemCastTime;       //0x78
            // 0x7C
        };

        struct MobQuestItem
        {
            UINT8 type;
            UINT8 typeId;
        };

        struct MobAttack
        {
            PAD(4);
            UINT16 type;
            bool enabled;
            PAD(1);
            UINT32 time;
            UINT8 range;
            PAD(1);
            UINT16 power;
            UINT16 addPower;
            Attribute attribute;
            UINT8 special;
        };

        struct MobItem
        {
            UINT32 grade;
            UINT32 dropRate;
        };

        struct MobInfo
        {
            UINT16 mobId;            //0x00
            MobName mobName;         //0x02
            UINT16 level;            //0x22
            UINT16 exp;              //0x24
            UINT8 ai;                //0x26
            PAD(1);
            UINT16 money1;           //0x28
            UINT16 money2;           //0x2A
            MobQuestItem questItem;  //0x2C
            PAD(2);
            UINT32 health;           //0x30
            UINT16 stamina;          //0x34
            UINT16 mana;             //0x36
            UINT16 dexterity;        //0x38
            UINT16 wisdom;           //0x3A
            UINT16 luck;             //0x3C
            UINT8 height;            //0x3E
            UINT8 size;              //0x3F
            Attribute attribute;     //0x40
            PAD(1);
            UINT16 defense;          //0x42
            UINT16 resistance;       //0x44
            // 0x46
            Array<bool, 15> resistState;
            // 0x55
            Array<UINT8, 6> resistSkill;
            UINT32 normalTime;       //0x5C
            UINT8 normalStep;        //0x60
            PAD(3);
            UINT32 chaseTime;        //0x64
            UINT8 chaseStep;         //0x68
            UINT8 chaseRange;        //0x69 
            PAD(2);
            // 0x4A1A53
            DWORD cooldown;          //0x6C
            PAD(8);
            UINT32 country;          //0x78
            // 0x7C
            Array<MobAttack, 3> attack;
            // 0xB8
            PAD(12);
            // 0xC4
            Array<MobItem, 9> mobItem;
            // 0x10C
        };

        struct ProductInfo
        {
            ProductCode productCode;     //0x00
            PAD(3);
            Array<UINT32, 24> itemId;    //0x18
            Array<UINT8, 24> itemCount;  //0x78
            UINT32 price;                //0x90
            ProductName productName;     //0x94
            PAD(1);
            // 0xC8
        };

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
            // Curse of Goddess, etc.
            BaseStatus
        };

        struct SkillAbility
        {
            UINT8 type;
            PAD(1);
            UINT16 value;
        };

        enum SkillId
        {
            FrenziedForce = 398,
            FrenziedFocus,
            FrenziedFinesse,
            FrenziedFortune
        };

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

        struct SkillInfo
        {
            UINT16 skillId;           //0x00
            UINT8 skillLv;            //0x02
            SkillName skillName;      //0x03
            PAD(1);
            UINT16 level;             //0x24 
            UINT8 country;            //0x26
            bool attackFighter;       //0x27
            bool defenseFighter;      //0x28
            bool patrolRogue;         //0x29
            bool shootRogue;          //0x2A
            bool attackMage;          //0x2B
            bool defenseMage;         //0x2C
            Grow grow;                //0x2D
            UINT8 skillPoint;         //0x2E
            UINT8 typeShow;           //0x2F
            UINT8 typeAttack;         //0x30
            UINT8 typeEffect;         //0x31
            UINT16 typeDetail;        //0x32
            // 0x34
            Array<bool, 15> needWeapon;
            bool shield;              //0x43
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
            UINT16 keepTime;          //0x5C
            PAD(2);
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

        static ItemInfo* GetItemInfo(int type/*eax*/, int typeId/*ecx*/);
        static MobInfo* GetMobInfo(int mobId/*eax*/);
        static KillCountStatus* GetKCStatusByCount(int country/*eax*/, ULONG killCount/*ebx*/);
        static int GetKCStatusMax(int country/*eax*/);
        static int GetKCStatusMaxKillCount(int country/*eax*/);
        static ProductInfo* GetProductInfo(const char* productCode/*eax*/);
        static SkillInfo* GetSkillInfo(int skillId/*eax*/, int skillLv/*edx*/);
    };
    #pragma pack(pop)
}
