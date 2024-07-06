#pragma once
#include <shaiya/include/common/Job.h>
#include "include/shaiya/common.h"

namespace shaiya
{
    enum struct GuildUserDataStatus : UINT8
    {
        EnterWorld = 1,
        LeaveWorld,
        EnterRankBattle
    };

    #pragma pack(push, 1)
    // GUILDUSER_DATA
    struct GuildUserData
    {
        ULONG charId;        //0x00
        UINT8 authLv;        //0x04
        Job job;             //0x05
        UINT16 level;        //0x06
        CharArray<21> name;  //0x09
        // 0x1E
        GuildUserDataStatus status;
        PAD(1);
        // 0x20
    };
    #pragma pack(pop)
}
