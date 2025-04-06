#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CNetwork
    {
        static void Send(void* buffer, int length);
    };
    #pragma pack(pop)
}
