#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common.h>
#include "SNode.h"

namespace shaiya
{
    #pragma pack(push, 1)
    template<class T>
    struct SSyncList
    {
        T* head;              //0x00
        T* cursor;            //0x04
        CRITICAL_SECTION cs;  //0x08
        int32_t count;        //0x20
        SNode memHead;        //0x24
        // 0x2C
    };
    #pragma pack(pop)

    static_assert(sizeof(SSyncList<void>) == 0x2C);
}
