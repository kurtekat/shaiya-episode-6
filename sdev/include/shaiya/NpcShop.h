#pragma once
#include <shaiya/include/common.h>
#include "Npc.h"
#include "ShopItem.h"

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

    #pragma pack(push, 1)
    struct NpcShop : Npc
    {
        NpcShopType type;   //0x124
        PAD(3);
        int32_t itemCount;  //0x128
        ShopItem* items;    //0x12C
        // 0x130
    };
    #pragma pack(pop)

    static_assert(sizeof(NpcShop) == 0x130);
}
