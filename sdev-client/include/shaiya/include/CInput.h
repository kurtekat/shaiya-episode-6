#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // 0x566EA0 ctor
    struct SDirectInput
    {
        PAD(48);                           //0x22B291C
        // e.g., 19
        int maxInputStrLen;                //0x22B294C  0x30
        PAD(4324);
        CharArray<256> imeCompStrAttr;     //0x22B3A34  0x1118
        CharArray<1024> imeCompStrClause;  //0x22B3B34  0x1218
        // 0x22B3F34  0x1618
        PAD(8);
        HWND hwnd;                         //0x22B3F3C  0x1620
        // e.g., 0x4090409
        HKL keyboardLayout;                //0x22B3F40  0x1624
        // e.g., 1033
        UINT16 localeId;                   //0x22B3F44  0x1628
        // e.g., 1252
        UINT16 codePage;                   //0x22B3F46  0x162A
        DWORD imeProperty;                 //0x22B3F48  0x162C
        BOOL isImeOpen;                    //0x22B3F4C  0x1630
        PAD(12);
        HMODULE imm32Dll;                  //0x22B3F5C  0x1640
        PAD(4);
        FARPROC imm32_GetReadingString;    //0x22B3F64  0x1648
        FARPROC imm32_ShowReadingWindow;   //0x22B3F68  0x164C
        // 0x1650
    };
    #pragma pack(pop)

    static_assert(sizeof(SDirectInput) == 0x1650);

    #pragma pack(push, 1)
    struct CInput
    {
        PAD(4);                        //0x22B24B8  0x00
        LPDIRECTINPUT8A directInput8;  //0x22B24BC  0x04
        PAD(1116);
        SDirectInput directInput;      //0x22B291C  0x464
        PAD(4);
        // 0x1AB8
    };
    #pragma pack(pop)

    static_assert(sizeof(CInput) == 0x1AB8);
}
