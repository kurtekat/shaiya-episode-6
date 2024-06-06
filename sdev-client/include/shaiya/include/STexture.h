#pragma once
#include <array>
#include "include/shaiya/common.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct STexture
    {
        PAD(4);                              //0x00
        std::array<char, 256> fileName;      //0x04
        std::array<char, 256> path;          //0x104
        LPDIRECT3DBASETEXTURE9 baseTexture;  //0x204
        // 0x208
    };
    #pragma pack(pop)
}
