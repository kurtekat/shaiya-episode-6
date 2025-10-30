#pragma once
#include <shaiya/include/common.h>
#include "common.h"

namespace shaiya
{
    struct STexture;

    #pragma pack(push, 1)
    struct SModelTexture
    {
        LPDIRECT3DVERTEXBUFFER9 vertexBuffer;  //0x00
        LPDIRECT3DINDEXBUFFER9 indexBuffer;    //0x04
        int32_t numVertexBufferIndices;        //0x08
        int32_t numIndexBufferIndices;         //0x0C
        int32_t numVertices;                   //0x10
        int32_t numFaces;                      //0x14
        PAD(4);
        STexture* texture;                     //0x1C
        // 0x20
    };
    #pragma pack(pop)

    static_assert(sizeof(SModelTexture) == 0x20);
}