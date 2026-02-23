#pragma once
#include <shaiya/include/common.h>
#include "common.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CButton
    {
        void* vftable;     //0x00
        bool enabled;      //0x04
        PAD(1);
        bool mouseEnter;   //0x06
        PAD(9);
        D2D_POINT_2U pos;  //0x10
        D2D_SIZE_U size;   //0x18
        PAD(131);
        bool checked;      //0xA3
        PAD(1332);
        // 0x5D8

        static void Init(CButton* button);
        static void Draw(CButton* button, int windowPosX, int windowPosY);
        static BOOL Func_0x54FEB0(CButton* button, int unknown);
        static BOOL Func_0x550A10(CButton* button);

        // So many parameters...geez.
        static void Func_0x551860(
            CButton* button, int windowPosX, int windowPosY, int param3, int param4, int param5, int param6, int param7, int param8, int param9,
            const char* fileName, int param11, int param12, 
            int param13, 
            float param14, float param15, float param16, float param17,
            float param18, float param19, float param20, float param21,
            float param22, float param23, float param24, float param25,
            float param26, float param27, float param28, float param29,
            float param30, float param31, float param32, float param33,
            int param34
        );

        static void Reset(CButton* button);
    };
    #pragma pack(pop)

    static_assert(sizeof(CButton) == 0x5D8);
}
