#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/SConnection.h>
#include <shaiya/include/common/SLog.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CLogConnection
    {
        SConnection connection;  //0x00
        PAD(16);
        SLog log;                //0xE0
        // 0x100
        PAD(8);
        // 0x108
    };
    #pragma pack(pop)

    static_assert(sizeof(CLogConnection) == 0x108);
    static auto g_pClientToLog = (CLogConnection*)0x10A2710; // 0x587970 (userLog)
}
