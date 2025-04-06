#pragma once
#include <cstdint>

namespace shaiya
{
    // Credit: Matias Ramirez (Parsec)
    enum struct NpcShopType : uint8_t
    {
        GenericMerchant,
        WeaponMerchant,
        ProtectionMerchant,
        AccessoryMerchant,
        LiquidMedicineMerchant,
        ProfessionalTrader,
        RidingMerchant,
        MantleMerchant,
        BadgeMerchant,
        BankTeller,
        GoldBarMerchant,
        ProfessionalBlacksmith1 = 15,
        ProfessionalBlacksmith2,
        Alchemist = 20,
        EtinManager = 100,
        EtinMerchant,
        AuctionBoard = 117
    };

    enum struct NpcTeam : int32_t
    {
        Light,
        Fury,
        Neutral
    };

    enum struct NpcType : uint8_t
    {
        Merchant = 1,
        GateKeeper,
        Blacksmith,
        VetManager,
        GamblingHouse,
        Warehouse,
        Normal,
        Guard,
        Animal,
        Apprentice,
        GuildMaster,
        Dead,
        SkillReset
    };
}
