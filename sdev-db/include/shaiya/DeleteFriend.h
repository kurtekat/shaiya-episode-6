#pragma once
#include <shaiya/include/common.h>
#include "SNode.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct DeleteFriend : SNode
    {
        uint32_t charId;  //0x08
        // 0x0C
    };
    #pragma pack(pop)

    static_assert(sizeof(DeleteFriend) == 0xC);
}
