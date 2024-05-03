#pragma once
#include "include/shaiya/common.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CNetwork
    {
        static void Send(void* buf, int len);
    };
    #pragma pack(pop)
}
