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
        T* head;              //0x00
        T* next;              //0x04
        CRITICAL_SECTION cs;  //0x08
        int count;            //0x20
        SNode node;           //0x24
        // 0x2C
    };
    #pragma pack(pop)
}
