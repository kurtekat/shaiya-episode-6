#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // SOCKADDR_IN
    struct SInternetAddress
    {
        // AF_INET
        USHORT family;
        USHORT port;
        ULONG ip;
        CharArray<8> zero;
    };
    #pragma pack(pop)

    static_assert(sizeof(SInternetAddress) == 0x10);
}
