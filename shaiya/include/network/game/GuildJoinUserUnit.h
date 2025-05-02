#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Job.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // GUILDJOINUSER_UNIT
    struct GuildJoinUserUnit
    {
        uint32_t charId;
        uint16_t level;
        Job job;
        String<21> charName;
    };
    #pragma pack(pop)
}
