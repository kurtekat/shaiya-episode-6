#pragma once
#include <shaiya/include/common.h>
#include "CItem.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct BaseItem : CItem
    {
        uint8_t bag;   //0x48
        uint8_t slot;  //0x49
        PAD(6);
        // 0x50
    };
    #pragma pack(pop)

    static_assert(sizeof(BaseItem) == 0x50);
}
