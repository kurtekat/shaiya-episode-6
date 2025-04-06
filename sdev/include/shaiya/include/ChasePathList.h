#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    struct ChasePathNode;

    #pragma pack(push, 1)
    struct ChasePathList
    {
        ChasePathNode* head;
    };
    #pragma pack(pop)

    static_assert(sizeof(ChasePathList) == 0x4);
}
