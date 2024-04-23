#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CMonitorNet
    {
        PAD(136);
        // 0x88
    };
    #pragma pack(pop)

    static auto g_pMonitorNet = (CMonitorNet*)0x10A28F8;
}
