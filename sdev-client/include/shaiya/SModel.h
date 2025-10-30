#pragma once
#include <shaiya/include/common.h>
#include "include/shaiya/common.h"
#include "SBoxAxis.h"

namespace shaiya
{
    struct MeshFace;
    struct SModelTexture;

    #pragma pack(push, 1)
    struct SModel
    {
        int32_t numTextures;               //0x00
        SModelTexture* textures;           //0x04
        String<256> fileName;              //0x08
        D3DVECTOR center;                  //0x108
        float distanceToCenter;            //0x114
        SBoxAxis viewBox;                  //0x118
        SBoxAxis collisionBox;             //0x130
        D3DVECTOR* collisionVertices;      //0x148
        MeshFace* collisionFaces;          //0x14C
        int32_t numCollisionVertices;      //0x150
        int32_t numCollisionFaces;         //0x154
        int32_t numCollisionFaceIndices;   //0x158
        int32_t numTextureFaces;           //0x15C
        int32_t numTextureVertices;        //0x160
        // 0x164
    };
    #pragma pack(pop)

    static_assert(sizeof(SModel) == 0x164);
}
