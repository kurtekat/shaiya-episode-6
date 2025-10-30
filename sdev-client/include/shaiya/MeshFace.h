#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct MeshFace
    {
        uint16_t vertexIndex1;
        uint16_t vertexIndex2;
        uint16_t vertexIndex3;
    };
    #pragma pack(pop)

    static_assert(sizeof(MeshFace) == 0x6);
}
