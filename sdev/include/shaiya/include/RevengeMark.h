#pragma once
#include <map>
#include <vector>
#include <shaiya/include/common.h>

namespace shaiya
{
    struct RevengeMark
    {
        uint32_t killerId;
        uint32_t killCount;
    };

    inline std::map<CharId, std::vector<RevengeMark>> g_revengeMark;
}
