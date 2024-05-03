#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SVector
    {
        float x;
        float y;
        float z;

        static double EuclideanDistance(SVector* u, SVector* v);
        static double Length(SVector* v);
    };
    #pragma pack(pop)

    static_assert(sizeof(SVector) == 0xC);
}
