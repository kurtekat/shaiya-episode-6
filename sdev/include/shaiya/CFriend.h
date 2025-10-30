#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common.h>
#include "BlockInfo.h"
#include "FriendInfo.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CFriend
    {
        int32_t friendCount;             //0x1838
        Array<FriendInfo, 100> friends;  //0x183C
        int32_t blockCount;              //0x377C  0x1F44
        Array<BlockInfo, 100> blocks;    //0x3780  0x1F48
        uint32_t requestSenderId;        //0x5530
        CRITICAL_SECTION cs;             //0x5534
    };
    #pragma pack(pop)

    static_assert(sizeof(CFriend) == 0x3D14);
}
