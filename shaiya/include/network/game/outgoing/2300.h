#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/network/game/MyShopUnit.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_MYSHOP_BUY_LIST
    template<class MyShopUnitT>
    struct GameMyShopItemListOutgoing
    {
        uint16_t opcode{ 0x230B };
        uint8_t itemCount;
        Array<MyShopUnitT, 20> itemList;

        constexpr static int baseLength = 3;
    };
    #pragma pack(pop)
}
