#pragma once
#include <shaiya/include/common.h>
#include "CObject.h"
#include "SNode.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CDoor : CObject, SNode
    {
        bool open;               //0x30
        PAD(3);
        tick32_t nextCloseTime;  //0x34
        tick32_t nextUseTime;    //0x38
        bool32_t autoClose;      //0x3C
        int32_t closeTime;       //0x40
        // 0x44
    };
    #pragma pack(pop)

    static_assert(sizeof(CDoor) == 0x44);
}
