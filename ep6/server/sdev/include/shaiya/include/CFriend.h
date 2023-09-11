#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CFriend
    {
        CharId id;        //0x00
        Country country;  //0x04
        Grow grow;        //0x05
        Job job;          //0x06
        char name[21];    //0x07
        char memo[51];    //0x1C
        PAD(1);
        // 0x50
    };
    #pragma pack(pop)
}
