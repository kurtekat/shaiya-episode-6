#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/MakeType.h>
#include "SaveType.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct BillingItemInfo
    {
        SaveType saveType;  //0x00
        PAD(3);
        uint8_t bag;        //0x07
        uint8_t slot;       //0x08
        PAD(7);
        uint64_t uniqueId;  //0x10
        uint32_t itemId;    //0x18
        uint8_t type;       //0x1C
        uint8_t typeId;     //0x1D
        uint8_t count;      //0x1E
        PAD(1);
        uint16_t quality;   //0x20
        PAD(2);
        time32_t makeTime;  //0x24
        MakeType makeType;  //0x28
        PAD(7);
        // 0x30
    };
    #pragma pack(pop)

    static_assert(sizeof(BillingItemInfo) == 0x30);
}
