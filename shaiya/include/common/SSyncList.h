#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Sentinel.h>
#include <shaiya/include/common/SNode.h>

namespace shaiya
{
    #pragma pack(push, 1)
    template<class T>
    // circular :/
    struct SSyncList
    {
        Sentinel sentinel;    //0x00
        CRITICAL_SECTION cs;  //0x08
        UINT32 count;         //0x20
        T* last;              //0x24
        T* first;             //0x28
        // 0x2C
    };
    #pragma pack(pop)

    static_assert(sizeof(SSyncList<void*>) == 0x2C);
}
