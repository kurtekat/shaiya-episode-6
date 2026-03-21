#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/network/game/MyShopUnit.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_MYSHOP_BUY_LIST
    struct GameMyShopBuyListOutgoing_EP5
    {
        uint16_t opcode{ 0x230B };
        uint8_t itemCount;
        Array<MyShopUnit_EP5, 20> itemList;

        constexpr static int baseLength = 3;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_MYSHOP_BUY_LIST
    struct GameMyShopBuyListOutgoing_EP6_4
    {
        uint16_t opcode{ 0x230B };
        uint8_t itemCount;
        Array<MyShopUnit_EP6_4, 20> itemList;

        constexpr static int baseLength = 3;
    };
    #pragma pack(pop)
}
