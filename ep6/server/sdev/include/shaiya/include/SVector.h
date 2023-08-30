#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SVector
    {
        float x;
        float y;
        float z;

        static double Distance2(SVector* pos1/*ecx*/, SVector* pos2/*eax*/);
    };
    #pragma pack(pop)
}
