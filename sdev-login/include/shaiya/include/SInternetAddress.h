#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // SOCKADDR_IN
    struct SInternetAddress
    {
        // AF_INET
        uint16_t family;
        uint16_t port;
        uint32_t ipv4;
        char zero[8];
    };
    #pragma pack(pop)

    static_assert(sizeof(SInternetAddress) == 0x10);
}
