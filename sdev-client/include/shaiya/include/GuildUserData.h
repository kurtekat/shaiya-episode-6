#pragma once
#include <shaiya/include/common/Job.h>
#include "include/shaiya/common.h"

namespace shaiya
{
    #pragma pack(push, 1)
    // GUILDUSER_DATA
    struct GuildUserData
    {
        ULONG charId;        //0x00
        UINT8 authLv;        //0x04
        Job job;             //0x05
        UINT16 level;        //0x06
        PAD(1);
        CharArray<21> name;  //0x09
        enum struct Status : UINT8
        {
            EnterWorld = 1,
            LeaveWorld,
            EnterRankBattle
        } status;            //0x1E
        PAD(1);
        // 0x20
    };
    #pragma pack(pop)

    static_assert(sizeof(GuildUserData) == 0x20);
}
