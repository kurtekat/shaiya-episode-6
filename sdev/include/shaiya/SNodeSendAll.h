#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>
#include "SNode.h"

namespace shaiya
{
    struct SPacketBufferSend;

    #pragma pack(push, 1)
    struct SNodeSendAll : SNode
    {
        int32_t type;               //0x08
        SPacketBufferSend* buffer;  //0x0C
        Country country;            //0x10
        PAD(3);
        uint32_t sid;               //0x14
        uint32_t did;               //0x18
        int32_t priority;           //0x1C
        // 0x20
    };
    #pragma pack(pop)

    static_assert(sizeof(SNodeSendAll) == 0x20);
}
