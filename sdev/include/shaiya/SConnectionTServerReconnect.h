#pragma once
#include <shaiya/include/common.h>
#include "SConnectionTServer.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct SConnectionTServerReconnect : SConnectionTServer
    {
        bool enableSend;  //0xD8
        PAD(7);
        // 0xE0
    };
    #pragma pack(pop)

    static_assert(sizeof(SConnectionTServerReconnect) == 0xE0);
}
