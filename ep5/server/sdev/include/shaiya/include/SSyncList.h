#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // thanks, Cups ^^
    struct SNode
    {
        SNode* prev;
        SNode* next;
    };

    template<class T>
    struct SSyncList
    {
        T* head;
        T* cursor;
        CRITICAL_SECTION cs;
        UINT size;
        SNode node;
    };
    #pragma pack(pop)
}
