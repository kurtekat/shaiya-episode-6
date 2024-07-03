#pragma once
#include "include/shaiya/common.h"
#include "include/shaiya/include/CPlayerData.h"
#include "include/shaiya/include/CWorldMgr.h"

namespace shaiya
{
    struct CStaticText;

    enum struct TargetType : int
    {
        None = -1,
        Mob,
        Item,
        User,
        Npc
    };

    #pragma pack(push, 1)
    // 00572D30 ctor
    struct Camera
    {
        D3DMATRIX world;           //0x22B69B0  0x00
        D3DMATRIX view;            //0x22B69F0  0x40
        D3DMATRIX projection;      //0x22B6A30  0x80
        D3DVECTOR pos;             //0x22B6A70  0xC0
        D3DVECTOR lookAt;          //0x22B6A7C  0xCC
        D3DVECTOR up;              //0x22B6A88  0xD8
        DXGI_RGB color;            //0x22B6A94  0xE4
        // Character->pos
        D3DVECTOR target;          //0x22B6AA0  0xF0
        D3DMATRIX mat1;            //0x22B6AAC  0xFC
        D3DMATRIX mat2;            //0x22B6AEC  0x13C
        D3DMATRIX mat3;            //0x22B6B2C  0x17C
        D3DMATRIX mat4;            //0x22B6B6C  0x1BC
        // 0x22B6BAC  0x1FC
        PAD(348);
        // 0x22B6D08  0x358
        LPDIRECT3DVERTEXBUFFER9 vertexBuffer1;
        // 0x22B6D0C  0x35C
        LPDIRECT3DVERTEXBUFFER9 vertexBuffer2;
        PAD(4);
        // 0x22B6D14  0x364
        D3DPRESENT_PARAMETERS presentParameters;
        LPD3DXFONT font1;          //0x22B6D4C  0x39C
        LPD3DXFONT font2;          //0x22B6D50  0x3A0
        LPD3DXFONT font3;          //0x22B6D54  0x3A4
        LPD3DXFONT font4;          //0x22B6D58  0x3A8
        HFONT hFont;               //0x22B6D5C  0x3AC
        PAD(96);
        LPDIRECT3D9 d3d9;          //0x22B6DC0  0x410
        LPDIRECT3DDEVICE9 device;  //0x22B6DC4  0x414
        PAD(8);
        CStaticText* staticText;   //0x22B6DD0  0x420
        PAD(3076);
        LPDIRECTDRAW directDraw;   //0x22B79D8  0x1028
        PAD(1544);
        // 0x1634
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // the .data section
    struct Static
    {
        PAD(216);                         //0x7AB000
        D2D_SIZE_U client;                //0x7AB0D8
        D3DVIEWPORT9 viewport;            //0x7AB0E0
        // 0x7AB0F8
        PAD(2788);
        // CUser->id, CMob->id, CNpc->id
        ULONG targetId;                   //0x7ABBDC
        TargetType targetType;            //0x7ABBE0
        PAD(84796);
        CharArray<MAX_PATH> iniFileName;  //0x7C0720
        // 0x7C0824
        PAD(1416);
        float fogStart;                   //0x7C0DAC
        float fogEnd;                     //0x7C0DB0
        PAD(28);
        CharArray<16> ipv4Addr;           //0x7C0DD0
        // 0x7C0DE0
        PAD(1468);
        HWND hwnd;                        //0x7C139C
        HINSTANCE hinst;                  //0x7C13A0
        PAD(1940);
        // <t>
        CharArray<512> t;                 //0x7C1B38
        PAD(1024);
        // <s>
        CharArray<512> s;                 //0x7C2138
        // <p>
        CharArray<512> p;                 //0x7C2338
        // <i>
        CharArray<512> i;                 //0x7C2538
        // 0x7C2738
        PAD(4);
        // <v>
        UINT32 v;                         //0x7C273C
        PAD(9000);
        CWorldMgr worldMgr;               //0x7C4A68
        // 0x906DE0
        PAD(25584);
        CPlayerData playerData;           //0x90D1D0
        // 0x22B0208
        PAD(6384);
        UINT32 killLv;                    //0x22B1AF8
        UINT32 deathLv;                   //0x22B1AFC
        PAD(2492);
        LPDIRECTINPUT8A directInput8;     //0x22B24BC
        PAD(6832);
        HIMC himc;                        //0x22B3F70
        PAD(6708);
        Array<wchar_t, 1024> wcharBuf1;   //0x22B59A8
        Array<wchar_t, 1024> wcharBuf2;   //0x22B61A8
        LPDIRECT3DDEVICE9 device;         //0x22B69A8
        PAD(4);
        Camera camera;                    //0x22B69B0
        // 0x22B7FE4
        PAD(16);
        float fps;                        //0x22B7FF4
        PAD(237504);
        LPDIRECTSOUND8 directSound8;      //0x22F1FB8
        PAD(33608);
        int socket;                       //0x22FA304
        PAD(21368);
        CharArray<MAX_PATH> exeFileName;  //0x22FF680
        // 0x22FF784
        PAD(708);
        HMODULE hModule;                  //0x22FFA48
        PAD(21940);
        // 0x2305000 (.rsrc)

        // static functions

        static void GetMsg(int type, int line, int unknown);
    };
    #pragma pack(pop)

    // access global variables
    inline auto g_var = (Static*)0x7AB000;
}
