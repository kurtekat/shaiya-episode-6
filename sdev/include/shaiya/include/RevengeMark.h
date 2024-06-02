#pragma once
#include <map>
#include <vector>

#include <shaiya/include/common.h>

namespace shaiya
{
    struct RevengeMark
    {
        ULONG killerId;
        UINT32 killCount;
    };

    inline std::map<CharId, std::vector<RevengeMark>> g_revengeMark;
}
