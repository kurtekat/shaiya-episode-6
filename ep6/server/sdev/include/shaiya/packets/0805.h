#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct LapisianAddRequest
    {
        UINT16 opcode; // 0x805
        UINT8 lapisianBag;
        UINT8 lapisianSlot;
        UINT8 enchantItemBag;
        UINT8 enchantItemSlot;
        UINT8 enchantItemCount;
        UINT8 upgradeItemBag;
        UINT8 upgradeItemSlot;
        UINT8 unknown;
        ULONG npcId;
    };
    #pragma pack(pop)
}
