#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct StatResetBackup
    {
        bool statusReset;       //0x00
        bool skillReset;        //0x01
        uint16_t statusPoints;  //0x02
        uint16_t strength;      //0x04
        uint16_t dexterity;     //0x06
        uint16_t intelligence;  //0x08
        uint16_t wisdom;        //0x0A
        uint16_t reaction;      //0x0C
        uint16_t luck;          //0x0E
        uint16_t skillPoints;   //0x10
        // 0x12
    };
    #pragma pack(pop)

    static_assert(sizeof(StatResetBackup) == 0x12);
}
