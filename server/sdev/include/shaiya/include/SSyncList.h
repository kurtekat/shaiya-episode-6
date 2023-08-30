#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/SNode.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // thanks, Cups ^^
    template<class T>
    struct SSyncList
    {
        T* head;
        T* cursor;
        CRITICAL_SECTION cs;
        UINT32 count;
        SNode node;
    };
    #pragma pack(pop)
}
