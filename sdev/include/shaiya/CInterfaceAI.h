#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CInterfaceAI
    {
        void* vftable;
    };
    #pragma pack(pop)

    static_assert(sizeof(CInterfaceAI) == 0x4);
}
