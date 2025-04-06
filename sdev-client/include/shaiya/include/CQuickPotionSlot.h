#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CQuickPotionSlot
    {
        uint8_t srcBag;      //0x00
        PAD(1);
        uint16_t srcSlot;    //0x02
        bool32_t filled;     //0x04
        // z and x
        int32_t itemType;    //0x08
        int32_t itemTypeId;  //0x0C
        // 0x10
    };
    #pragma pack(pop)

    static_assert(sizeof(CQuickPotionSlot) == 0x10);
}
