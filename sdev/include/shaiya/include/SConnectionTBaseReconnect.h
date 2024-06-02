#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    struct SConnection;

    #pragma pack(push, 1)
    struct SConnectionTBaseReconnect
    {
        static void Send(SConnection* connection, void* buf, int len);
    };
    #pragma pack(pop)
}
