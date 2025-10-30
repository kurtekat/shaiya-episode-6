#pragma once
#include <shaiya/include/common.h>
#include "SNode.h"

namespace shaiya
{
    struct CObject;

    #pragma pack(push, 1)
    struct CObjectLink : SNode
    {
        CObject* object;
        // 0xC
    };
    #pragma pack(pop)

    static_assert(sizeof(CObjectLink) == 0xC);
}
