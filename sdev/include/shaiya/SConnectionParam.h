#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common.h>
#include "SNode.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct SConnectionParam : SNode2
    {
        int closeType;                //0x10
        int closeError;               //0x14
        uint64_t sendCount;           //0x18
        uint64_t recvCount;           //0x20
        uint64_t totalSendBytes;      //0x28
        uint64_t totalRecvBytes;      //0x30
        tick32_t connectTime;         //0x38
        int32_t sendProcessingCount;  //0x3C
        int32_t dispatchJobCount;     //0x40
        tick32_t recvReplyTime;       //0x44
        CRITICAL_SECTION cs;          //0x48
        // 0x60
    };
    #pragma pack(pop)

    static_assert(sizeof(SConnectionParam) == 0x60);
}
