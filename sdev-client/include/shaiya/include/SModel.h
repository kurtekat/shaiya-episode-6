#pragma once
#include "include/shaiya/common.h"

namespace shaiya
{
    struct STexture;

    #pragma pack(push, 1)
    struct SModelTexture
    {
        LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
        LPDIRECT3DINDEXBUFFER9 indexBuffer;
        UINT32 numVertexBufferIndices;  //0x08
        UINT32 numIndexBufferIndices;   //0x0C
        UINT32 numVertices;             //0x10
        UINT32 numFaces;                //0x14
        PAD(4);
        STexture* texture;              //0x1C
        // 0x20
    };
    #pragma pack(pop)

    static_assert(sizeof(SModelTexture) == 0x20);

    #pragma pack(push, 1)
    struct SModel
    {
        UINT32 numTextures;              //0x00
        SModelTexture* textures;         //0x04
        CharArray<256> fileName;         //0x08
        D3DVECTOR center;                //0x108
        float distanceToCenter;          //0x114
        BoundingBox viewBox;             //0x118
        BoundingBox collisionBox;        //0x130
        D3DVECTOR* collisionVertices;    //0x148
        MeshFace* collisionFaces;        //0x14C
        UINT32 numCollisionVertices;     //0x150
        UINT32 numCollisionFaces;        //0x154
        UINT32 numCollisionFaceIndices;  //0x158
        UINT32 numTextureFaces;          //0x15C
        UINT32 numTextureVertices;       //0x160
        // 0x164
    };
    #pragma pack(pop)

    static_assert(sizeof(SModel) == 0x164);
}
