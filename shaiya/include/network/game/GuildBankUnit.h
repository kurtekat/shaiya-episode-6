#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/CraftName.h>
#include <shaiya/include/common/Gems.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_GUILD_BANK_UNIT
    struct GuildBankUnit
    {
        uint8_t slot;
        uint8_t type;
        uint8_t typeId;
        uint16_t quality;
        Gems gems;
        uint8_t count;
        CraftName craftName;
    };
    #pragma pack(pop)
}
