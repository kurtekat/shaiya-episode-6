#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    struct SPacketBufferSend;
    struct SQueuePrioritySendNode;

    #pragma pack(push, 1)
    struct SQueuePrioritySendNode
    {
        int32_t priority;
        SPacketBufferSend* data;
        SQueuePrioritySendNode* next;
    };
    #pragma pack(pop)

    static_assert(sizeof(SQueuePrioritySendNode) == 0xC);
}
