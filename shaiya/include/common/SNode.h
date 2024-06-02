#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // thanks, Cups ^^
    struct SNode
    {
        SNode* prev;
        SNode* next;
    };
    #pragma pack(pop)
}
