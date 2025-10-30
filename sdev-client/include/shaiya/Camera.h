#pragma once
#include <shaiya/include/common.h>
#include "common.h"

namespace shaiya
{
    struct CStaticText;
    struct CVertexShader;

    #pragma pack(push, 1)
    // 00572D30 ctor
    struct Camera
    {
        D3DXMATRIX world;           //0x22B69B0  0x00
        D3DXMATRIX view;            //0x22B69F0  0x40
        D3DXMATRIX projection;      //0x22B6A30  0x80
        D3DVECTOR pos;              //0x22B6A70  0xC0
        D3DVECTOR lookAt;           //0x22B6A7C  0xCC
        D3DVECTOR up;               //0x22B6A88  0xD8
        D3DVECTOR vec1;             //0x22B6A94  0xE4
        D3DVECTOR target;           //0x22B6AA0  0xF0
        D3DXMATRIX mat1;            //0x22B6AAC  0xFC
        D3DXMATRIX mat2;            //0x22B6AEC  0x13C
        D3DXMATRIX mat3;            //0x22B6B2C  0x17C
        D3DXMATRIX mat4;            //0x22B6B6C  0x1BC
        D3DXMATRIX mat5;            //0x22B6BAC  0x1FC
        // 0x22B6BEC  0x23C
        PAD(260);
        D3DCOLOR fogColor;          //0x22B6CF0  0x340
        PAD(20);
        // 0x22B6D08  0x358
        LPDIRECT3DVERTEXBUFFER9 vertexBuffer1;
        // 0x22B6D0C  0x35C
        LPDIRECT3DVERTEXBUFFER9 vertexBuffer2;
        // 0x22B6D10  0x360
        CVertexShader* vertexShader;
        // 0x22B6D14  0x364
        D3DPRESENT_PARAMETERS presentParameters;
        LPD3DXFONT d3dxFont3;       //0x22B6D4C  0x39C
        LPD3DXFONT d3dxFont2;       //0x22B6D50  0x3A0
        LPD3DXFONT d3dxFont1;       //0x22B6D54  0x3A4
        LPD3DXFONT d3dxFont0;       //0x22B6D58  0x3A8
        HFONT hFont;                //0x22B6D5C  0x3AC
        int32_t text0Width;         //0x22B6D60  0x3B0
        int32_t text1Width;         //0x22B6D64  0x3B4
        int32_t text0Height;        //0x22B6D68  0x3B8
        int32_t text1Height;        //0x22B6D6C  0x3BC
        uint32_t textColorR;        //0x22B6D70  0x3C0
        uint32_t textColorG;        //0x22B6D74  0x3C4
        uint32_t textColorB;        //0x22B6D78  0x3C8
        D3DMATERIAL9 material;      //0x22B6D7C  0x3CC
        LPDIRECT3D9 d3d9;           //0x22B6DC0  0x410
        LPDIRECT3DDEVICE9 device;   //0x22B6DC4  0x414
        uint32_t primitiveCount;    //0x22B6DC8  0x418
        bool32_t enableInfoText;    //0x22B6DCC  0x41C
        CStaticText* staticText;    //0x22B6DD0  0x420
        PAD(4);
        D3DGAMMARAMP gammaRamp1;    //0x22B6DD8  0x428
        D3DGAMMARAMP gammaRamp2;    //0x22B73D8  0xA28
        LPDIRECTDRAW directDraw;    //0x22B79D8  0x1028
        D3DGAMMARAMP gammaRamp3;    //0x22B79DC  0x102C
        PAD(4);
        D3DCOLOR clearDeviceColor;  //0x22B7FE0  0x1630
        // 0x1634
    };
    #pragma pack(pop)

    static_assert(sizeof(Camera) == 0x1634);
}
