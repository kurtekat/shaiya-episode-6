#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct InsZonePortal
    {
        int32_t id;
        int32_t country;
    };
    #pragma pack(pop)

    static_assert(sizeof(InsZonePortal) == 0x8);
}
