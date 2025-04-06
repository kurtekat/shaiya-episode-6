#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common.h>

namespace shaiya
{
    struct SQueueStatusNode;

    #pragma pack(push, 1)
    struct SSyncQueueStatus
    {
        SQueueStatusNode* front;  //0x00
        SQueueStatusNode* back;   //0x04
        CRITICAL_SECTION cs;      //0x08
        int32_t count;            //0x20
        // 0x24
    };
    #pragma pack(push)

    static_assert(sizeof(SSyncQueueStatus) == 0x24);
}
