#pragma once

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

    static_assert(sizeof(SNode) == 0x8);
}
