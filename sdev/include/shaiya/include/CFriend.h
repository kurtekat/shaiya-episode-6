#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/Job.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct BlockList
    {
        ULONG charId;            //0x00
        CharArray<21> charName;  //0x04
        CharArray<51> memo;      //0x19
        // 0x4C
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CFriend
    {
        ULONG charId;            //0x00
        Country country;         //0x04
        Grow grow;               //0x05
        Job job;                 //0x06
        CharArray<21> charName;  //0x07
        CharArray<51> memo;      //0x1C
        PAD(1);
        // 0x50
    };
    #pragma pack(pop)
}
