#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    struct CItem;

    #pragma pack(push, 1)
    // 00411260 ctor
    struct CObjectMgr
    {
        PAD(36);
        CRITICAL_SECTION cs24;
        PAD(60);
        CRITICAL_SECTION cs48;
        PAD(60);
        CRITICAL_SECTION cs6C;
        PAD(60);
        CRITICAL_SECTION cs90;
        PAD(60);
        CRITICAL_SECTION csB4;
        PAD(60);
        CRITICAL_SECTION csD8;
        PAD(60);
        CRITICAL_SECTION csFC;
        PAD(60);
        CRITICAL_SECTION cs120;
        PAD(60);
        CRITICAL_SECTION cs144;
        PAD(60);
        CRITICAL_SECTION cs168;
        PAD(60);
        CRITICAL_SECTION cs18C;
        // 0x1A4

        static void FreeItem(CItem* item/*edi*/);
    };
    #pragma pack(pop)

    // 0x587964
    static auto g_pObjectMgr = (CObjectMgr*)0x10A239C;
}
