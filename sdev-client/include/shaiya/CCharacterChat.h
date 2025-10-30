#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    struct SStaticText;

    #pragma pack(push, 1)
    struct CCharacterChat
    {
        PAD(8);
        SStaticText* text;
        // 0x74823C 1.5
        float yAdd;
        // 0x10
    };
    #pragma pack(pop)

    static_assert(sizeof(CCharacterChat) == 0x10);
}
