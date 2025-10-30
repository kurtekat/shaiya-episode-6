#pragma once
#include <shaiya/include/common.h>
#include "SNode.h"

namespace shaiya
{
    struct CZone;

    #pragma pack(push, 1)
    struct CZoneLink : SNode
    {
        CZone* zone;  //0x08
        // 0xC
    };
    #pragma pack(pop)

    static_assert(sizeof(CZoneLink) == 0xC);
}
