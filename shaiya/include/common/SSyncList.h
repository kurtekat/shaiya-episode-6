#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/SNode.h>

namespace shaiya
{
    #pragma pack(push, 1)
    template<class T>
    struct SSyncListElement
    {
        SNode node;
        T data;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct SSyncListSentinel
    {
        SNode* tail;
        SNode* head;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    template<class T>
    // circular :/
    struct SSyncList
    {
        SSyncListSentinel sentinel;
        CRITICAL_SECTION cs;
        UINT32 count;
        SSyncListElement<T>* last;
        SSyncListElement<T>* first;
        // 0x2C
    };
    #pragma pack(pop)
}
