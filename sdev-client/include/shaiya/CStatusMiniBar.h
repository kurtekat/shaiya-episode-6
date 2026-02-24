#pragma once
#include <shaiya/include/common.h>
#include "common.h"
#include "CButton.h"
#include "CTexture.h"
#include "CWindow.h"

namespace shaiya
{
    struct CMessage;

    #pragma pack(push, 1)
    struct CStatusMiniBar : CWindow
    {
        PAD(8);
        void* vftable;          //0x2C
        CTexture image1;        //0x30  main_stats_light
        CTexture image2;        //0x40  main_stats_bar_bg
        CTexture image3;        //0x50  main_stats_bar
        CTexture image4;        //0x60  main_stats_circle
        CTexture image5;        //0x70  main_stats_circle2
        float hpBarLen;         //0x80
        float spBarLen;         //0x84
        float mpBarLen;         //0x88
        int v8C;                //0x8C
        float v90;              //0x90
        D2D_SIZE_F size;        //0x94
        D2D_SIZE_F size3;       //0x9C
        D2D_SIZE_F size4;       //0xA4
        D2D_POINT_2F namePos;   //0xAC
        D2D_POINT_2F levelPos;  //0xB4
        D2D_POINT_2F facePos;   //0xBC
        D2D_POINT_2F hpBarPos;  //0xC4
        D2D_POINT_2F hpPos;     //0xCC
        D2D_POINT_2F mpBarPos;  //0xD4
        D2D_POINT_2F mpPos;     //0xDC
        D2D_POINT_2F spBarPos;  //0xE4
        D2D_POINT_2F spPos;     //0xEC
        // 0xF4
    };
    #pragma pack(pop)

    static_assert(sizeof(CStatusMiniBar) == 0xF4);

    #pragma pack(push, 1)
    struct CStatusMiniBar_EP7 : CWindow
    {
        PAD(8);
        void* vftable;          //0x2C
        CTexture image1;        //0x30  main_stats_light
        CTexture image2;        //0x40  main_stats_bar_bg
        CTexture image3;        //0x50  main_stats_bar
        CTexture image4;        //0x60  main_stats_circle
        CTexture image5;        //0x70  main_stats_circle2
        float hpBarLen;         //0x80
        float spBarLen;         //0x84
        float mpBarLen;         //0x88
        int v8C;                //0x8C
        float v90;              //0x90
        CButton button;         //0x94  main_stats_pvp_button
        CTexture image6;        //0x66C main_stats_pvp
        float alpha6;           //0x67C
        // Not implemented
        DWORD lastMoveTime;     //0x680
        bool enabled;           //0x684
        //
        PAD(3);
        CMessage* message;      //0x688
        void* v68C;             //0x68C
        void* v690;             //0x690
        void* v694;             //0x694
        D2D_SIZE_F size;        //0x69C
        D2D_SIZE_F size3;       //0x6A0
        D2D_SIZE_F size4;       //0x6A8
        D2D_POINT_2F namePos;   //0x6B0
        D2D_POINT_2F levelPos;  //0x6B8
        D2D_POINT_2F facePos;   //0x6C0
        D2D_POINT_2F hpBarPos;  //0x6C8
        D2D_POINT_2F hpPos;     //0x6D0
        D2D_POINT_2F mpBarPos;  //0x6D8
        D2D_POINT_2F mpPos;     //0x6E0
        D2D_POINT_2F spBarPos;  //0x6E8
        D2D_POINT_2F spPos;     //0x6F0
        // 0x6F8
    };
    #pragma pack(pop)

    static_assert(sizeof(CStatusMiniBar_EP7) == 0x6F8);
}
