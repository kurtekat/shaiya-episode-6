#pragma once
#include <shaiya/include/common.h>
#include "common.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CTexture
    {
        // D3DRTYPE_TEXTURE
        LPDIRECT3DTEXTURE9 texture;
        PAD(4);
        D2D_SIZE_F size;
        // 0x10

        static int CreateFromFile(CTexture* texture, const char* path, const char* fileName/*.tga*/, int w, int h);
        static void Render(CTexture* texture, int x, int y, float z);
        // to-do: name the last 4 parameters
        static void Render(CTexture* texture, D3DCOLOR diffuse, 
            int x, int y, float z, 
            int w, int h, 
            float a, float b, float c, float d
        );
        static void Reset(CTexture* texture);
    };
    #pragma pack(pop)

    static_assert(sizeof(CTexture) == 0x10);
}
