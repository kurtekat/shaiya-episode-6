#pragma once
#include <shaiya/include/common.h>
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
}
