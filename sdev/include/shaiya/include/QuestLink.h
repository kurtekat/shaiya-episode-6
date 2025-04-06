#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct QuestLink
    {
        int32_t startCount;
        uint16_t* startIds;
        int32_t endCount;
        uint16_t* endIds;
        // 0x10
    };
    #pragma pack(pop)

    static_assert(sizeof(QuestLink) == 0x10);
}
