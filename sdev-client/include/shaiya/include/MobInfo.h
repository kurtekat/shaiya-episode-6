#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Attribute.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct MobInfo
    {
        char* name;           //0x00
        uint16_t model;       //0x04
        uint16_t level;       //0x06
        uint32_t ai;          //0x08
        uint32_t health;      //0x0C
        // not wings
        uint8_t height;       //0x10
        uint8_t radius;       //0x11
        Attribute attribute;  //0x12
        PAD(1);
        uint32_t delay;       //0x14
        uint8_t range;        //0x18
        PAD(3);
        uint32_t chaseDelay;  //0x1C
        uint8_t chaseRange;   //0x20
        PAD(31);
        bool32_t isWings;     //0x40
        // 0x44
    };
    #pragma pack(pop)

    static_assert(sizeof(MobInfo) == 0x44);
}
