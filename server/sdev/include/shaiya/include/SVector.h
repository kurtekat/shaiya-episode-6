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
        static double Length(SVector* v);
        static void Normalize(SVector* v/*esi*/);
    };
    #pragma pack(pop)
}
