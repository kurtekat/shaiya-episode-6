#pragma once
#include <shaiya/include/common.h>
#include "SConnectionTBase.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct SConnectionTBaseReconnect : SConnectionTBase
    {
        bool enableSend;  //0xD8
        PAD(7);
        // 0xE0

        static void Send(SConnection* connection, void* packet, int length);
    };
    #pragma pack(pop)

    static_assert(sizeof(SConnectionTBaseReconnect) == 0xE0);
}
