#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/SNode.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct Sentinel
    {
        SNode* tail;
        SNode* head;
    };
    #pragma pack(pop)
}
