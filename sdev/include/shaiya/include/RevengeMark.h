#pragma once
#include <map>
#include <vector>

namespace shaiya
{
    using CharId = unsigned long;

    struct RevengeMark
    {
        uint32_t killerId;
        uint32_t killCount;
    };

    inline std::map<CharId, std::vector<RevengeMark>> g_revengeMark;
}
