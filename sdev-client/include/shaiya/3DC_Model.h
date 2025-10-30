#pragma once
#include <shaiya/include/common.h>
#include "common.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct _3DC_Model
    {
        LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
        LPDIRECT3DINDEXBUFFER9 indexBuffer;
        PAD(20);
        int32_t numVertices;     //0x1C
        int32_t numFaces;        //0x20
        int32_t numFaceIndices;  //0x24
        int32_t numBones;        //0x28
        D3DMATRIX* bones;        //0x2C
        PAD(8);
        String<260> path;        //0x38
        uint16_t unknown;        //0x13C
        PAD(2);
        // 333, 444
        int32_t version;         //0x140
        // 0x144
    };
    #pragma pack(pop)

    static_assert(sizeof(_3DC_Model) == 0x144);
}
