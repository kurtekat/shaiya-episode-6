#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    FWDDECL QuestInfo;

    static Address g_QuestData = 0x4093300;

    #pragma pack(push, 1)
    struct CQuestData
    {
        static QuestInfo* GetQuest(int questId/*eax*/);
    };
    #pragma pack(pop)
}
