#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/network/game/BankUnit.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_SHOP_SELL
    struct GameShopSellOutgoing
    {
        uint16_t opcode{ 0x703 };
        uint8_t result;
        uint8_t bag;
        uint8_t slot;
        uint8_t type;
        uint8_t typeId;
        uint8_t count;
        uint32_t money;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_CHAR_BANK
    template<class BankUnitT, size_t UnitCount>
    struct GameCharBankOutgoing
    {
        uint16_t opcode{ 0x711 };
        uint32_t bankMoney;
        uint8_t itemCount;
        Array<BankUnitT, UnitCount> itemList;

        constexpr static int baseLength = 7;
    };
    #pragma pack(pop)
}
