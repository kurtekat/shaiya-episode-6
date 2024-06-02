#pragma once
#pragma warning(disable: 4005)
#define DIRECTINPUT_VERSION 0x800
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#include <dxgi.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <d2d1.h>
#include <ddraw.h>
#include <dinput.h>
#include <dsound.h>
#include <dwrite.h>

#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct BoundingBox
    {
        D3DVECTOR lowerLimit;
        D3DVECTOR upperLimit;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct MeshFace
    {
        UINT16 vertexIndex1;
        UINT16 vertexIndex2;
        UINT16 vertexIndex3;
    };
    #pragma pack(pop)
}
