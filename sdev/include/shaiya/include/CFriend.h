#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/Job.h>

namespace shaiya
{
    using Memo = std::array<char, 51>;

    #pragma pack(push, 1)
    struct BlockList
    {
        ULONG charId;       //0x00
        CharName charName;  //0x04
        Memo memo;          //0x19
        // 0x4C
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CFriend
    {
        ULONG charId;       //0x00
        Country country;    //0x04
        Grow grow;          //0x05
        Job job;            //0x06
        CharName charName;  //0x07
        Memo memo;          //0x1C
        PAD(1);
        // 0x50
    };
    #pragma pack(pop)
}
