#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/SLog.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ClientToLog
    {
        PAD(224);
        SLog log;  //0xE0
        // 0x100
        PAD(8);
        // 0x108
    };
    #pragma pack(pop)

    // 0x587968 (session)
    static void* g_pClientToMgr = (void*)0x10A2540;
    // 0x58796C (dbAgent)
    static void* g_pClientToDBAgent = (void*)0x10A2628;
    // 0x587970 (userLog)
    static ClientToLog* g_pClientToLog = (ClientToLog*)0x10A2710;
    // 0x587974 (gameLog)
    static void* g_pClientToGameLog = (void*)0x10A2818;

    #pragma pack(push, 1)
    struct SConnectionTBaseReconnect
    {
        static void Send(void* clientTo, void* buf, int len);
    };
    #pragma pack(pop)
}
