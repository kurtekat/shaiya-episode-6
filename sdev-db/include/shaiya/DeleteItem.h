#pragma once
#include <shaiya/include/common.h>
#include "SNode.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct DeleteItem : SNode
    {
        uint64_t uniqueId;  //0x08
        // 0x10
    };
    #pragma pack(pop)

    static_assert(sizeof(DeleteItem) == 0x10);
}
