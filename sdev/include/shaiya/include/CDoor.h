#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/SVector.h>

namespace shaiya
{
    enum struct DoorCountry : UINT32
    {
        Neutral,
        Light,
        Fury
    };

    #pragma pack(push, 1)
    struct CDoor
    {
        InsZoneId insZoneId;  //0x00
        SVector pos;          //0x04
        ULONG id;             //0x10
        DoorCountry country;  //0x14
        UINT32 minLevel;      //0x18
        UINT32 maxLevel;      //0x1C
        UINT32 destMapId;     //0x20
        SVector destPos;      //0x24
        // 0x30
    };
    #pragma pack(pop)
}
