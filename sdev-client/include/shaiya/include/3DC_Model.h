#pragma once
#include "include/shaiya/common.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct _3DC_Model
    {
        LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
        LPDIRECT3DINDEXBUFFER9 indexBuffer;
        PAD(20);
        UINT32 numVertices;        //0x1C
        UINT32 numFaces;           //0x20
        UINT32 numFaceIndices;     //0x24
        UINT32 numBones;           //0x28
        D3DMATRIX* bones;          //0x2C
        PAD(8);
        CharArray<MAX_PATH> path;  //0x38
        UINT16 unknown;            //0x13C
        PAD(2);
        // 333, 444
        UINT32 version;            //0x140
        // 0x144
    };
    #pragma pack(pop)

    static_assert(sizeof(_3DC_Model) == 0x144);
}
