#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CMonitorNet
    {
        PAD(136);
        // 0x88
    };
    #pragma pack(pop)

    static_assert(sizeof(CMonitorNet) == 0x88);
    static auto g_pMonitorNet = (CMonitorNet*)0x10A28F8;
}
