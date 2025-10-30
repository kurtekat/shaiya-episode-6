#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    template<class T, int = -1>
    struct StackStateMachine
    {
        PAD(68);
        // 0x44
    };
    #pragma pack(pop)

    static_assert(sizeof(StackStateMachine<void, -1>) == 0x44);
}
