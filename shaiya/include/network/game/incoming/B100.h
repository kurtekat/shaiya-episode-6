#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct GameBillingItemBankToBagIncoming
    {
        uint16_t opcode{ 0xB102 };
        uint8_t npcSlot;
        uint32_t npcId;
    };
    #pragma pack(pop)
}
