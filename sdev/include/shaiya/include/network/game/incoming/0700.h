#pragma once
#include <shaiya/include/common.h>

// CUser::PacketShop

namespace shaiya
{
    #pragma pack(push, 1)
    struct ItemBagToNpcShopIncoming
    {
        UINT16 opcode{ 0x703 };
        UINT8 bag;
        UINT8 slot;
        UINT8 count;
        ULONG npcId;
    };
    #pragma pack(pop)
}
