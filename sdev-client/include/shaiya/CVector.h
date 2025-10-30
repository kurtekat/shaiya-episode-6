#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    template<class T>
    struct CVector
    {
        PAD(24);
    };
    #pragma pack(pop)

    static_assert(sizeof(CVector<void>) == 0x18);
}
