#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/UserTypes.h>

namespace shaiya
{
    enum struct GuildUserDataStatus : uint8_t
    {
        EnterWorld = 1,
        LeaveWorld,
        EnterRankBattle
    };

    #pragma pack(push, 1)
    // GUILDUSER_DATA
    struct GuildUserData
    {
        uint32_t charId;      //0x00
        uint8_t authLv;       //0x04
        Job job;              //0x05
        uint16_t level;       //0x06
        PAD(1);
        String<21> charName;  //0x09
        // 0x1E
        GuildUserDataStatus status;
        PAD(1);
        // 0x20
    };
    #pragma pack(pop)

    static_assert(sizeof(GuildUserData) == 0x20);
}
