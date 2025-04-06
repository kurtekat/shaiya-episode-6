#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TPC_SHOP_SELL
    struct GameShopSellIncoming
    {
        uint16_t opcode{ 0x703 };
        uint8_t bag;
        uint8_t slot;
        uint8_t count;
        uint32_t npcId;
    };
    #pragma pack(pop)
}
