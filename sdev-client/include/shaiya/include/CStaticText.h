#pragma once
#include "include/shaiya/common.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CStaticText
    {
        // D3DRTYPE_TEXTURE
        LPDIRECT3DBASETEXTURE9 texture;  //0x00
        D2D_SIZE_U size;                 //0x04
        //

        static CStaticText* Init(const char* text);
        static void Draw(CStaticText* staticText, long x, long y, float extrusion, D3DCOLOR argb);
        static long GetPointX(CStaticText* staticText);
    };
    #pragma pack(pop)
}
