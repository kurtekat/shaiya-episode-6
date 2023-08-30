#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SVector
    {
        float x;
        float y;
        float z;

        static double EuclideanDistance(SVector* u, SVector* v);
    };
    #pragma pack(pop)
}
