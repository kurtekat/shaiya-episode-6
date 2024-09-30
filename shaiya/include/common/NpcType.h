#pragma once
#include <cstdint>

namespace shaiya
{
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

    enum struct NpcType32 : uint32_t
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

    // Credit: Matias Ramirez (Parsec)
    enum struct MerchantType : uint8_t
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
        ProfessionalBlacksmith = 15,
        EtinManager = 100,
        EtinSeller,
        AuctionBoard = 117
    };
}