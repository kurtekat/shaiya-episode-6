#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/UserTypes.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // GUILDJOINUSER_UNIT
    struct GuildJoinUserUnit
    {
        uint32_t charId;
        uint16_t level;
        Job job;
        CharName charName;
    };
    #pragma pack(pop)
}
