#pragma once
#include <shaiya/include/common.h>
#include "SaveType.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct BlockInfo
    {
        SaveType saveType;    //0x00
        uint32_t charId;      //0x04
        String<21> charName;  //0x08
        String<51> memo;      //0x1E
        // 0x50
    };
    #pragma pack(pop)

    static_assert(sizeof(BlockInfo) == 0x50);
}
