#pragma once
#include <shaiya/include/common.h>
#include "common.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct SStaticText
    {
        LPDIRECT3DTEXTURE9 texture;
        D2D_SIZE_U size;
        // 0xC
    };
    #pragma pack(pop)

    static_assert(sizeof(SStaticText) == 0xC);

    #pragma pack(push, 1)
    // 0x22B6DD0
    struct CStaticText
    {
        LPDIRECT3DSURFACE9 unknown1;
        LPDIRECT3DSURFACE9 unknown2;
        LPDIRECT3DSURFACE9 unknown3;
        LPDIRECT3DSURFACE9 unknown4;
        // D3DFMT_X8R8G8B8
        D3DFORMAT format;
        // 0x14

        static SStaticText* Create(const char* text);
        static void Draw(SStaticText* staticText, int x, int y, float z, D3DCOLOR color);
        static int GetTextWidth(const char* text);
    };
    #pragma pack(pop)

    static_assert(sizeof(CStaticText) == 0x14);
}
