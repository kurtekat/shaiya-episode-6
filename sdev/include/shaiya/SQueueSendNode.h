#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    struct SPacketBufferSend;

    #pragma pack(push, 1)
    struct SQueueSendNode
    {
        SPacketBufferSend* data;
        SQueueSendNode* next;
    };
    #pragma pack(pop)

    static_assert(sizeof(SQueueSendNode) == 0x8);
}
