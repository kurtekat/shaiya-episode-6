#pragma once
#include "include/shaiya/common.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct STexture
    {
        PAD(4);                          //0x00
        CharArray<256> fileName;         //0x04
        CharArray<256> path;             //0x104
        LPDIRECT3DBASETEXTURE9 texture;  //0x204
        // 0x208
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CTexture
    {
        // D3DRTYPE_TEXTURE
        LPDIRECT3DBASETEXTURE9 texture;
        PAD(4);
        D2D_SIZE_F size;
        // 0x10

        static BOOL CreateFromFile(CTexture* texture, const char* path, const char* fileName/*.tga*/, long w, long h);
        static void Draw(CTexture* texture, long x, long y, float extrusion);
        static void Draw(CTexture* texture, float top, float left, float right, float bottom);
    };
    #pragma pack(pop)
}
