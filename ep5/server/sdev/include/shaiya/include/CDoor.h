#pragma once
#include <shaiya/common.h>
#include <shaiya/include/SVector.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CDoor
    {
        UINT32 insZoneId;  //0x00
        SVector pos;       //0x04
        ULONG id;          //0x10
        UINT32 country;    //0x14
        UINT32 minLevel;   //0x18
        UINT32 maxLevel;   //0x1C
        UINT32 outMapId;   //0x20
        SVector outPos;    //0x24
        // 0x30
    };
    #pragma pack(pop)
}
