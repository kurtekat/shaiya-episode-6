#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    struct SConnection;

    struct SConnectionTBaseReconnect
    {
        static void Send(SConnection* connection, void* packet, int length);
    };
}
