#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    enum struct NpcType8 : UINT8
    {
        Merchant = 1,
        GateKeeper,
        Blacksmith,
        VetManager,
        GamblingHouse,
        Warehouse,
        Normal,
        Guard,
        Animal,
        Apprentice,
        GuildMaster,
        Dead,
        SkillReset
    };

    enum struct NpcType32 : UINT32
    {
        Merchant = 1,
        GateKeeper,
        Blacksmith,
        VetManager,
        GamblingHouse,
        Warehouse,
        Normal,
        Guard,
        Animal,
        Apprentice,
        GuildMaster,
        Dead,
        SkillReset
    };
}