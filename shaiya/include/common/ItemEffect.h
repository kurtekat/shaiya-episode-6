#pragma once
#include <cstdint>

namespace shaiya
{
    enum struct ItemEffect : uint8_t
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
        EnergyCrystal,
        EquipMale,
        EquipFemale,
        PerfectLinkingHammer = 69,
        MobGen = 73,
        PremiumLapisiaLv1 = 76,
        PremiumLapisiaLv2,
        PremiumLapisiaLv3,
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
        SafetyCharm,
        TownMoveScroll,
        TransferRubiksCube,
        Catalyst,
        EnchantEnhancer,
        Dye = 110,
        HaloReactor,
        Spellbook,
        EternalContinuousResurrect,
        EternalPreventItemDrop,
        EternalPreventExpDrop,
        TyrosStone,
        AbsoluteRecreationRune,
        NpcRecall = 200,
        Item500 = 210,
        // pick-up pets
        PetGold = 212,
        PetItem,
        PetGoldItem
    };
}
