#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common.h>

namespace shaiya
{
    struct SPacketBufferSend;

    #pragma pack(push, 1)
    struct SSyncQueueBuffer
    {
        SPacketBufferSend* front;  //0x00
        SPacketBufferSend* back;   //0x04
        CRITICAL_SECTION cs;       //0x08
        int32_t count;             //0x20
        // 0x24
    };
    #pragma pack(pop)

    static_assert(sizeof(SSyncQueueBuffer) == 0x24);
}
