#pragma once
#include <shaiya/include/common.h>
#include "CTexture.h"
#include "CWindow.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CQuickSlot : CWindow
    {
        PAD(8);
        CTexture mainImage;  //0x2C
        CTexture plusImage;  //0x3C
        uint8_t bag;         //0x4C
        PAD(203);
        bool change;         //0x118
        bool plus;           //0x119
        PAD(10);
        uint8_t id;          //0x124
        PAD(3);
        // 0x128

        static CQuickSlot* Create(void* block, int id);
        static int BagToBag(CQuickSlot* quickSlot, int bag, int slot);
        static CQuickSlot* Reset(CQuickSlot* quickSlot, bool free);
    };
    #pragma pack(pop)

    static_assert(sizeof(CQuickSlot) == 0x128);
}
