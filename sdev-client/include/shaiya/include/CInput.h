#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    /*
    Login input limit:
        Japan: 12
        Russia: 31
        Default: 19

    Chat input limit:
        Taiwan: 70
        HongKong: 70
        Default: 120
    */

    #pragma pack(push, 1)
    // 0x566EA0 ctor
    struct SDirectInput
    {
        PAD(48);                           //0x22B291C
        UINT32 maxStrLen;                  //0x22B294C  0x30
        BOOL disableChkChars;              //0x22B2950  0x34
        PAD(92);
        Array<wchar_t, 8> wideString;      //0x22B29B0  0x94
        UINT32 wideStrLen;                 //0x22B29C0  0xA4
        // 0x22B29B0 becomes wchar_t* if > 7
        UINT32 wideChkStrLen;              //0x22B29C4  0xA8
        PAD(4);
        CharArray<16> ansiString;          //0x22B29CC  0xB0
        UINT32 ansiStrLen;                 //0x22B29DC  0xC0
        // 0x22B29CC becomes char* if > 15
        UINT32 ansiChkStrLen;              //0x22B29E0  0xC4
        PAD(32);
        bool disableNonNumericChars;       //0x22B2A04  0xE8
        CharArray<2048> ansiBuffer;        //0x22B2A05  0xE9
        Array<wchar_t, 1024> wideBuffer;   //0x22B3205  0x8E9
        // 0x22B3A05  0x10E9
        PAD(47);
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
