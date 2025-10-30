#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common.h>

namespace shaiya
{
    struct SQueuePrioritySendNode;

    #pragma pack(push, 1)
    struct SSyncQueueBufferPriority
    {
        SQueuePrioritySendNode* front;  //0x00
        SQueuePrioritySendNode* back;   //0x04
        int32_t totalLength;            //0x08
        CRITICAL_SECTION cs;            //0x0C
        int32_t count;                  //0x24
        // 0x28
    };
    #pragma pack(pop)

    static_assert(sizeof(SSyncQueueBufferPriority) == 0x28);
}
