#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    // to-do
    enum struct TargetType : int32_t
    {
    };

    #pragma pack(push, 1)
    struct Target
    {
        TargetType type;
        uint32_t objectId;
        // 0x8
    };
    #pragma pack(pop)

    static_assert(sizeof(Target) == 0x8);
}
