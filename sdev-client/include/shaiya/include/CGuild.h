#pragma once
#include "include/shaiya/common.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CGuild
    {
        ULONG id;                  //0x00
        CharArray<25> name;        //0x04
        CharArray<21> masterName;  //0x1D
        CharArray<65> remark;      //0x32
        UINT8 rank;                //0x73
        UINT32 points;             //0x74
        // 0x78
    };
    #pragma pack(pop)
}
