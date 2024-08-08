#pragma once
#include "include/shaiya/common.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct STexture
    {
        PAD(4);                      //0x00
        CharArray<256> fileName;     //0x04
        CharArray<256> path;         //0x104
        LPDIRECT3DTEXTURE9 texture;  //0x204
        // 0x208
    };
    #pragma pack(pop)

    static_assert(sizeof(STexture) == 0x208);

    #pragma pack(push, 1)
    struct CTexture
    {
        // D3DRTYPE_TEXTURE
        LPDIRECT3DTEXTURE9 texture;
        PAD(4);
        D2D_SIZE_F size;
        // 0x10

        static BOOL CreateFromFile(CTexture* texture, const char* path, const char* fileName/*.tga*/, long w, long h);
        static void Render(CTexture* texture, long x, long y, float z);
        // to-do: name the last 4 parameters
        static void Render(CTexture* texture, D3DCOLOR diffuse, 
            long x, long y, float z, 
            long w, long h, 
            float a, float b, float c, float d
        );
    };
    #pragma pack(pop)

    static_assert(sizeof(CTexture) == 0x10);
}
