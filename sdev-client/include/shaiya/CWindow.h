#pragma once
#include <shaiya/include/common.h>
#include "common.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CWindow
    {
        void* vftable;                   //0x00
        D2D_POINT_2U pos;                //0x04
        D2D_SIZE_U size;                 //0x0C
        bool32_t leftMouseButtonDown;    //0x14
        D2D_POINT_2U leftMouseClickPos;  //0x18
        bool32_t visible;                //0x20
        // 0x24

        static void Draw(LPDIRECT3DBASETEXTURE9 texture, int x, int y);
    };
    #pragma pack(pop) 

    static_assert(sizeof(CWindow) == 0x24);
}
