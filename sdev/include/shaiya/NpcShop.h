#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/NpcTypes.h>
#include "Npc.h"
#include "ShopItem.h"

namespace shaiya
{
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
