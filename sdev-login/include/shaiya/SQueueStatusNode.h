#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SQueueStatusNode
    {
        SQueueStatusNode* next;
        int32_t status;
    };
    #pragma pack(push)

    static_assert(sizeof(SQueueStatusNode) == 0x8);
}
