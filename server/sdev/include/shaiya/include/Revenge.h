#pragma once
#include <map>
#include <vector>

#include <include/shaiya/common.h>

namespace shaiya
{
    struct Revenge
    {
        CharId killerId;
        UINT32 killCount;
    };

    inline std::map<CharId, std::vector<Revenge>> g_revengeMark;
}
