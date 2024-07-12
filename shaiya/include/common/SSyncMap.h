#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/SNode.h>

namespace shaiya
{
    // to-do

    #pragma pack(push, 1)
    template<class Key, class Value>
    struct SSyncMap
    {
        CRITICAL_SECTION cs;  //0x00
        PAD(28);
        UINT32 count;         //0x34
        PAD(16);
        // 0x48
    };
    #pragma pack(pop)

    static_assert(sizeof(SSyncMap<void, void>) == 0x48);
}
