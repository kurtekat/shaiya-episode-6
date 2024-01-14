#pragma once
#include <map>
#include <vector>

#include <include/shaiya/common.h>

namespace shaiya
{
    struct RevengeMark
    {
        CharId killerId;
        UINT32 killCount;
    };

    inline std::map<CharId, std::vector<RevengeMark>> g_revengeMark;
}
