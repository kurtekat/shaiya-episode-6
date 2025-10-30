#pragma once
#include <shaiya/include/common.h>
#include "CObject.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CObjectMoveable : CObject
    {
        int32_t sendMoveCount;  //0x28
        // 0x2C
    };
    #pragma pack(pop)

    static_assert(sizeof(CObjectMoveable) == 0x2C);
}
