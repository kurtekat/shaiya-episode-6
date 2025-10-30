#pragma once
#include <shaiya/include/common.h>
#include "SConnectionTBaseReconnect.h"
#include "SLog.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CLogConnection : SConnectionTBaseReconnect, SLog
    {
        bool logNetSend;  //0x100
        PAD(7);
        // 0x108
    };
    #pragma pack(pop)

    static_assert(sizeof(CLogConnection) == 0x108);
    static auto g_pClientToLog = (CLogConnection*)0x10A2710; // 0x587970 (userLog)
}
