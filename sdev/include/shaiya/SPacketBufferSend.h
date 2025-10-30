#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SPacketBufferSend
    {
        void* vftable;            //0x00
        void* data;               //0x04
        int32_t refCount;         //0x08
        int32_t customRefCount;   //0x0C
        SPacketBufferSend* next;  //0x10
        // 0x14
    };
    #pragma pack(pop)

    static_assert(sizeof(SPacketBufferSend) == 0x14);
}
