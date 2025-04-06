#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ChasePathNode
    {
        int32_t posX;
        int32_t posZ;
        ChasePathNode* next;
    };
    #pragma pack(pop)

    static_assert(sizeof(ChasePathNode) == 0xC);
}
