#pragma once
#include "include/shaiya/common.h"
#include "include/shaiya/include/CTexture.h"
#include "include/shaiya/include/CWindow.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CQuickSlot
    {
        CWindow window;      //0x00
        PAD(8);
        CTexture mainImage;  //0x2C
        CTexture plusImage;  //0x3C
        UINT8 bag;           //0x4C
        PAD(203);
        bool change;         //0x118
        bool plus;           //0x119
        PAD(10);
        UINT8 id;            //0x124
        PAD(3);
        // 0x128

        static CQuickSlot* Create(void* block, int id);
        static BOOL BagToBag(CQuickSlot* quickSlot, int bag, int slot);
        static CQuickSlot* Reset(CQuickSlot* quickSlot, bool free);
    };
    #pragma pack(pop)

    static_assert(sizeof(CQuickSlot) == 0x128);
}
