#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct MobInfo
    {
        char* name;           //0x00
        UINT16 model;         //0x04
        UINT16 level;         //0x06
        UINT32 ai;            //0x08
        UINT32 health;        //0x0C
        // not wings
        UINT8 height;         //0x10
        UINT8 radius;         //0x11
        Attribute attribute;  //0x12
        PAD(1);
        UINT32 delay;         //0x14
        UINT8 range;          //0x18
        PAD(3);
        UINT32 chaseDelay;    //0x1C
        UINT8 chaseRange;     //0x20
        PAD(28);
        BOOL isWings;         //0x40
        // 0x44
    };
    #pragma pack(pop)
}
