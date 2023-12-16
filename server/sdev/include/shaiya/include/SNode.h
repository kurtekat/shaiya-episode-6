#pragma once
#include <sdev/include/shaiya/common.h>

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
