#pragma once
#include <array>
#include <cstdint>

namespace shaiya
{
    using NpcId = unsigned long;
    using QuestId = uint16_t;

    using QuestName = std::array<char, 32>;

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
