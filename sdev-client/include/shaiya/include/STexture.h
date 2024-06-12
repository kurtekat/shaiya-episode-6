#pragma once
#include "include/shaiya/common.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct STexture
    {
        PAD(4);                   //0x00
        CharArray<256> fileName;  //0x04
        CharArray<256> path;      //0x104
        // 0x204
        LPDIRECT3DBASETEXTURE9 baseTexture;
        // 0x208
    };
    #pragma pack(pop)
}
