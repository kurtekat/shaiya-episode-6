#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/SNode.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CDead
    {
        PAD(50);
        Country country;  //0x32
        PAD(45);
        // 0x60
    };
    #pragma pack(pop)
}
