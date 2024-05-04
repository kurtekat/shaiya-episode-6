#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    enum struct _3dcVersion : UINT32
    {
        v333 = 0x14D,
        v444 = 0x1BC
    };

    #pragma pack(push, 1)
    struct _3dc
    {
        LPDIRECT3DVERTEXBUFFER9 vertexBuffer;  //0x00
        LPDIRECT3DINDEXBUFFER9 indexBuffer;    //0x04
        PAD(20);
        UINT32 numVertices;                    //0x1C
        UINT32 numFaces;                       //0x20
        UINT32 numFaceIndices;                 //0x24
        UINT32 numBones;                       //0x28
        D3DMATRIX* bones;                      //0x2C
        PAD(8);
        Array<char, MAX_PATH> path;            //0x38
        UINT16 unknown;                        //0x13C
        PAD(2);
        _3dcVersion version;                   //0x140
        // 0x144
    };
    #pragma pack(pop)
}
