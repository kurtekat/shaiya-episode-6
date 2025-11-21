#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/Job.h>
#include "SaveType.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct FriendInfo
    {
        SaveType saveType;    //0x00
        uint32_t charId;      //0x04
        Job job;              //0x08
        String<21> charName;  //0x09
        String<51> memo;      //0x1E
        Family family;        //0x51
        Grow grow;            //0x52
        PAD(1);
        // 0x54
    };
    #pragma pack(pop)

    static_assert(sizeof(FriendInfo) == 0x54);
}
