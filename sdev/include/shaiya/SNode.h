#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SNode
    {
        SNode* prev;  //0x00
        SNode* next;  //0x04
    };
    #pragma pack(pop)

    static_assert(sizeof(SNode) == 0x8);

    #pragma pack(push, 1)
    struct SNode2 : SNode
    {
        SNode2* prev2;  //0x08
        SNode2* next2;  //0x0C
    };
    #pragma pack(pop)

    static_assert(sizeof(SNode2) == 0x10);
}
