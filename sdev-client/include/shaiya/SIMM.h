#pragma once
#include <dimm.h>
#include <shaiya/include/common.h>
#include "common.h"

namespace shaiya
{
    #pragma pack(push, 1)
    // 005678B0 ctor
    struct SIMM
    {
        void* vftable;          //0x22B3F74  0x00
        HMODULE imm32Dll;       //0x22B3F78  0x04
        FARPROC immLockIMC;     //0x22B3F7C  0x08
        FARPROC immUnlockIMC;   //0x22B3F80  0x0C
        FARPROC immLockIMMC;    //0x22B3F84  0x10
        FARPROC immUnlockIMMC;  //0x22B3F88  0x14
        // 0x18

        static INPUTCONTEXT* LockIMC(HIMC himc);
        static int UnlockIMC(HIMC himc);
        static void* LockIMCC(HIMCC himcc);
        static int UnlockIMCC(HIMCC himcc);
    };
    #pragma pack(pop)
}
