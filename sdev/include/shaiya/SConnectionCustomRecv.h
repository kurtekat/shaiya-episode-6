#pragma once
#include <shaiya/include/common.h>
#include "SConnection.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct SConnectionCustomRecv : SConnection
    {
    };
    #pragma pack(pop)

    static_assert(sizeof(SConnectionCustomRecv) == 0xD0);
}
