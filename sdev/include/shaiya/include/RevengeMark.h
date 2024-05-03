#pragma once
#include <map>
#include <vector>
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct RevengeMark
    {
        ULONG killerId;
        UINT32 killCount;
    };
    #pragma pack(pop)

    inline std::map<CharId, std::vector<RevengeMark>> g_revengeMark;
}
