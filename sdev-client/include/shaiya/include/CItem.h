#pragma once
#include <shaiya/include/common/ItemTypes.h>
#include "include/shaiya/common.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CItem
    {
        UINT8 slotCount;      //0x00
        UINT8 type;           //0x01
        UINT8 typeId;         //0x02
        UINT8 count;          //0x03
        UINT16 quality;       //0x04
        Gems gems;            //0x06
        CraftName craftName;  //0x0C
        PAD(3);
        BOOL isBagToBag;      //0x24
        ULONG fromDate;       //0x28
        ULONG toDate;         //0x2C
        PAD(4);
        // 0x34
    };
    #pragma pack(pop)

    static_assert(sizeof(CItem) == 0x34);
}
