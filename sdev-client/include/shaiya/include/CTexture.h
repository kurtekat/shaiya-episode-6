#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CTexture
    {
        // D3DRTYPE_TEXTURE
        LPDIRECT3DBASETEXTURE9 texture;  //0x00
        PAD(4);
        D2D_SIZE_F size;                 //0x08
        // 0x10

        static void Draw(CTexture* texture, long x, long y, float extrusion);
        static void Draw(CTexture* texture, float top, float left, float right, float bottom);
    };
    #pragma pack(pop)
}
