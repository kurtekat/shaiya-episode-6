#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CClientToMgr
    {
        static void OnRecv(void* packet);
    };
    #pragma pack(pop)
}
