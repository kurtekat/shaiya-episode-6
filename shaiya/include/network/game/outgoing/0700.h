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
    struct GameCharBankOutgoing_EP5
    {
        uint16_t opcode{ 0x711 };
        uint32_t bankMoney;
        uint8_t itemCount;
        Array<BankUnit_EP5, 50> itemList;

        constexpr static int baseLength = 7;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_CHAR_BANK
    struct GameCharBankOutgoing_EP6_4
    {
        uint16_t opcode{ 0x711 };
        uint32_t bankMoney;
        uint8_t itemCount;
        Array<BankUnit_EP6_4, 40> itemList;

        constexpr static int baseLength = 7;
    };
    #pragma pack(pop)
}
