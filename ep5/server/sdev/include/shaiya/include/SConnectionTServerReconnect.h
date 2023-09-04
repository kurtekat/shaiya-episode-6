#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    // 0x58796C
    static Address g_pClientToDBAgent = 0x10A2628;

    #pragma pack(push, 1)
    struct SConnectionTServerReconnect
    {
        static void Send(void* buf, int len);
    };
    #pragma pack(pop)
}
