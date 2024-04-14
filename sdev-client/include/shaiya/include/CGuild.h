#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    typedef Array<char, 25> GuildName;
    typedef Array<char, 65> GuildRemark;

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
