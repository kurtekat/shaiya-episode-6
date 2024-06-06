#pragma once
#include <array>
#include <shaiya/include/user/CharName.h>
#include <shaiya/include/user/GuildName.h>
#include "include/shaiya/common.h"

namespace shaiya
{
    using GuildRemark = std::array<char, 65>;

    #pragma pack(push, 1)
    struct CGuild
    {
        ULONG id;             //0x00
        GuildName name;       //0x04
        CharName masterName;  //0x1D
        GuildRemark remark;   //0x32
        UINT8 rank;           //0x73
        UINT32 points;        //0x74
        // 0x78
    };
    #pragma pack(pop)
}
