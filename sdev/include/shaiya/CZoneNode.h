#pragma once
#include <shaiya/include/common.h>
#include "SSyncHeap.h"
#include "SSyncList.h"
#include "SSyncMap.h"

namespace shaiya
{
    struct CMap;
    struct CZone;

    #pragma pack(push, 1)
    struct CZoneNode
    {
        CMap* map;                  //0x00
        CZone* zone;                //0x04
        // 0x08
        SSyncMap<uint32_t, CZone*> zoneMap;
        SSyncList<CZone> zoneList;  //0x50
        SSyncHeap<CZone> zoneHeap;  //0x7C
        // 0xA0
    };
    #pragma pack(pop)

    static_assert(sizeof(CZoneNode) == 0xA0);
}
