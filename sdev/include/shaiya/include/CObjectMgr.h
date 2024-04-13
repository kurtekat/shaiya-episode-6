#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    struct CItem;

    struct CObjectMgr
    {
        static void FreeItem(CItem* item/*edi*/);
    };
}
