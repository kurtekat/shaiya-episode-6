#pragma once
#include <shaiya/include/common.h>
#include "SNode.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct DeleteQuest : SNode
    {
        uint16_t questId;  //0x08
        PAD(2);
        // 0x0C
    };
    #pragma pack(pop)

    static_assert(sizeof(DeleteQuest) == 0xC);
}
