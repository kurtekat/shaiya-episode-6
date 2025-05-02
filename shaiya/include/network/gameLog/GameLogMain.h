#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_GAMELOG_MAIN
    struct GameLogMain
    {
        uint16_t opcode;
        uint32_t billingId;
        String<32> username;
        uint32_t charId;
        String<21> charName;
        uint16_t level;
        uint32_t exp;
        uint16_t mapId;
        float x;
        float y;
        float z;
        time32_t actionTime;
    };
    #pragma pack(pop)
}
