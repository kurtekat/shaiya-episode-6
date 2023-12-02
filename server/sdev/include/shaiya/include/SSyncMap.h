#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/SNode.h>

namespace shaiya
{
    // to-do

    #pragma pack(push, 1)
    template<class Key, class Value>
    struct SSyncMap
    {
        CRITICAL_SECTION cs;  //0x00
        PAD(28);
        int count;            //0x34
        PAD(16);
        // 0x48
    };
    #pragma pack(pop)
}
