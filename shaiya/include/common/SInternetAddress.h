#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SInternetAddress
    {
        // AF_INET
        USHORT family;
        USHORT port;
        ULONG ip;
        PAD(8);
    };
    #pragma pack(pop)
}
