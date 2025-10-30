#pragma once
#include <shaiya/include/common.h>
#include "SNode.h"

namespace shaiya
{
    struct QuestInfo;

    #pragma pack(push, 1)
    struct CQuest : SNode
    {
        uint32_t id;              //0x08
        bool success;             //0x0C
        PAD(3);
        tick32_t startTime;       //0x10
        tick32_t endTime;         //0x14
        tick32_t endSuccessTime;  //0x18
        uint8_t count1;           //0x1C
        uint8_t count2;           //0x1D
        uint8_t count3;           //0x1E
        PAD(1);
        QuestInfo* info;          //0x20
        // 0x24
    };
    #pragma pack(pop)

    static_assert(sizeof(CQuest) == 0x24);
}
