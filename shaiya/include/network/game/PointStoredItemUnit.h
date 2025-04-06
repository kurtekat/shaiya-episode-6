#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // POINT_STORED_ITEMUNIT
    struct PointStoredItemUnit
    {
        uint8_t npcSlot;
        uint8_t type;
        uint8_t typeId;
        uint8_t count;
    };
    #pragma pack(pop)
}
