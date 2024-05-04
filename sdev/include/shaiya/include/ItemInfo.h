#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    typedef Array<char, 32> ItemName;

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

    enum struct ItemCountry : UINT8
    {
        Human,
        Elf,
        Light,
        DeathEater,
        Vail,
        Fury,
        Neutral
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
        Teleportation
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

    #pragma pack(push, 1)
    struct ItemInfo
    {
        UINT32 itemId;              //0x00
        ItemName itemName;          //0x04
        UINT8 type;                 //0x24
        UINT8 typeId;               //0x25
        ItemCountry country;        //0x26
        ReqJob job;                 //0x27
        PAD(1);
        UINT16 level;               //0x2E
        Grow grow;                  //0x30
        ItemReqOg reqOg;            //0x31
        UINT8 reqIg;                //0x32
        PAD(1);
        UINT16 reqVg;               //0x34
        UINT16 reqStr;              //0x36
        UINT16 reqDex;              //0x38
        UINT16 reqRec;              //0x3A
        UINT16 reqInt;              //0x3C
        UINT16 reqWis;              //0x3E
        UINT16 reqLuc;              //0x40
        UINT16 range;               //0x42
        UINT8 attackTime;           //0x44
        Attribute attribute;        //0x45
        ItemEffect effect;          //0x46
        UINT8 slotCount;            //0x47
        UINT8 speed;                //0x48
        UINT8 exp;                  //0x49
        UINT8 composeCount;         //0x4A
        UINT8 count;                //0x4B
        UINT16 maxQuality;          //0x4C
        UINT16 midQuality;          //0x4E
        UINT16 lowQuality;          //0x50
        UINT16 maxAtkPower;         //0x52
        UINT16 maxAtkPowerMidQ;     //0x54
        UINT16 maxAtkPowerLowQ;     //0x56
        UINT16 minAtkPower;         //0x58
        UINT16 minAtkPowerMidQ;     //0x5A
        UINT16 minAtkPowerLowQ;     //0x5C
        UINT16 defense;             //0x5E
        UINT16 defenseMidQ;         //0x60
        UINT16 defenseLowQ;         //0x62
        UINT16 resistance;          //0x64
        UINT16 resistanceMidQ;      //0x66
        UINT16 resistanceLowQ;      //0x68
        UINT16 health;              //0x6A
        UINT16 stamina;             //0x6C
        UINT16 mana;                //0x6E
        UINT16 strength;            //0x70
        UINT16 dexterity;           //0x72
        UINT16 reaction;            //0x74
        UINT16 intelligence;        //0x76
        UINT16 wisdom;              //0x78
        UINT16 luck;                //0x7A
        UINT32 dropGrade;           //0x7C
        UINT32 buy;                 //0x80
        UINT32 sell;                //0x84
        // not used
        UINT32 itemLimit;           //0x88
        PAD(20);
        ItemRealType realType;      //0xA0
        ItemMarketType marketType;  //0xA4
        PAD(3);
        // 0xA8
    };
    #pragma pack(pop)
}
