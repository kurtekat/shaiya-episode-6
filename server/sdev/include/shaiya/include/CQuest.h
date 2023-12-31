#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/SNode.h>

namespace shaiya
{
    struct QuestInfo;

    #pragma pack(push, 1)
    struct CQuest
    {
        SNode node;            //0x00
        UINT16 id;             //0x08
        PAD(22);
        QuestInfo* questInfo;  //0x20
        // 0x24
    };
    #pragma pack(pop)
}
