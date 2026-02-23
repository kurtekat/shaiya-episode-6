#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CMessage
    {
        PAD(3184);
        // 0xC70

        static CMessage* Init(void* message, int buttonsFlag, int textR, int textG, int textB, const char* text, int bgImageFlag);
        static int DialogResult(CMessage* message);
        static void Show(CMessage* message);
        static void Hide(CMessage* message);
    };
    #pragma pack(pop)

    static_assert(sizeof(CMessage) == 0xC70);
}
