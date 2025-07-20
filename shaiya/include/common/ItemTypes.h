#pragma once
#include <array>
#include <cstdint>

namespace shaiya
{
    using Gems = std::array<uint8_t, 6>;
    using CloakInfo = Gems;
    using CraftName = std::array<char, 21>;

    #pragma pack(push, 1)
    template<size_t N>
    struct ItemList
    {
        std::array<uint8_t, N> type;
        std::array<uint8_t, N> typeId;
    };
    #pragma pack(pop)

    template<size_t N>
    using ItemQuality = std::array<uint16_t, N>;

    template<size_t N>
    using ItemQualityLv = std::array<uint8_t, N>;

    enum struct Bag : uint8_t
    {
        Warehouse = 100,
        Bank = 200,
        Unknown = 250,
        GuildWarehouse = 255,
        Skill = 100,
        BasicAction = 101
    };

    struct EquipmentSlot
    {
        enum
        {
            Helmet,
            UpperArmor,
            LowerArmor,
            Gloves,
            Boots,
            Weapon,
            Shield,
            Cloak,
            Necklace,
            Ring1,
            Ring2,
            Bracelet1,
            Bracelet2,
            Vehicle,
            Pet,
            Costume,
            Wings,

            // Not supported

            Index17,
            Index18,
            Index19,
            Index20,
            Index21,
            Index22,
            Index23
        };
    };

    enum struct ItemEffect : uint8_t
    {
        HypnosisCure = 1,
        StunCure,
        SilenceCure,
        DarknessCure,
        StopCure,
        SlowCure,
        FaintProtection,
        DeathProtection,
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
        TargetResurrection,
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
        GemAddItemProtect,
        ExtractionHammer,
        MoveWar,
        RecreationRune = 62,
        EnergyCrystal,
        EquipMale,
        EquipFemale,
        PerfectLinkingHammer = 69,
        MobGen = 73,
        PremiumLapisiaLv1 = 76,
        PremiumLapisiaLv2,
        PremiumLapisiaLv3,
        CrowleyEssence = 85,
        StrRecreationRune,
        DexRecreationRune,
        IntRecreationRune,
        WisRecreationRune,
        RecRecreationRune,
        LucRecreationRune,
        CrowleyLiquid,
        StrVial,
        DexVial,
        IntVial,
        WisVial,
        RecVial,
        LucVial,
        ChaoticSquare,
        DungeonMap,
        CraftingHammer = 102,
        LapisianAddItemProtect,
        TownMoveScroll,
        ItemAbilityTransfer,
        Catalyst,
        EnchantEnhancer,
        Dye = 110,
        HaloReactor,
        Spellbook,
        EternalContinuousResurrection,
        EternalPreventItemDrop,
        EternalPreventExpDrop,
        TyrosStone,
        AbsoluteRecreationRune,
        NpcRecall = 200,
        Item500 = 210,
        PetPickGoldDrop = 212,
        PetPickItemDrop,
        PetPickDrop
    };

    enum struct ItemType : uint8_t
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
        LightHelmet,
        LightUpperArmor,
        LightLowerArmor,
        LightShield,
        LightGloves,
        LightBoots,
        Ring,
        Necklace,
        LightCloak,
        Consumable25,
        Gold,
        Quest27,
        Quest28,
        Quest29,
        Lapis,
        FuryHelmet,
        FuryUpperArmor,
        FuryLowerArmor,
        FuryShield,
        FuryGloves,
        FuryBoots,
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
        DualWeapon2,
        DualWeapon3,
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
        LightHelmet2,
        LightUpperArmor2,
        LightLowerArmor2,
        LightShield2,
        LightGloves2,
        LightBoots2,
        LightHelmet3,
        LightUpperArmor3,
        LightLowerArmor3,
        LightShield3,
        LightGloves3,
        LightBoots3,
        Consumable78,
        Consumable79,
        Consumable80,
        FuryHelmet2,
        FuryUpperArmor2,
        FuryLowerArmor2,
        FuryShield2,
        FuryGloves2,
        FuryBoots2,
        FuryHelmet3,
        FuryUpperArmor3,
        FuryLowerArmor3,
        FuryShield3,
        FuryGloves3,
        FuryBoots3,
        Unknown93,
        GoldBar,
        Lapisian,
        Necklace2,
        Bracelet2,
        Lapis98,
        Quest99,
        Other100,
        Other101,
        Other102,
        Other103,
        Pet = 120,
        Wings,
        Costume = 150
    };

    enum struct MakeType : char
    {
        Billing = 'B',
        MobDrop = 'D',
        G = 'G',
        QuestResult = 'Q',
        S = 'S',
        Exchange = 'T',
        UserDrop = 'U',
        V = 'V',
        CashShop = 'X'
    };

    enum struct ReqOg : uint8_t
    {
        Tradable,
        AccountBound,
        CharacterBound
    };
}
