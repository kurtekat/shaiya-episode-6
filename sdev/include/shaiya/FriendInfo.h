#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/Job.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct FriendInfo
    {
        uint32_t charId;      //0x00
        Family family;        //0x04
        Grow grow;            //0x05
        Job job;              //0x06
        String<21> charName;  //0x07
        String<51> memo;      //0x1C
        PAD(1);
        // 0x50
    };
    #pragma pack(pop)

    static_assert(sizeof(FriendInfo) == 0x50);
}
