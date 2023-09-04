#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    FWDDECL QuestInfo;

    #pragma pack(push, 1)
    struct CQuest
    {
        PAD(8);
        UINT16 questId;        //0x08
        PAD(22);
        QuestInfo* questInfo;  //0x20
        //
    };
    #pragma pack(pop)
}
