#include "include/shaiya/include/CQuestData.h"
using namespace shaiya;

QuestInfo* CQuestData::GetQuest(int questId/*eax*/)
{
    unsigned u0x47A5D0 = 0x47A5D0;

    __asm
    {
        mov ecx,g_QuestData
        mov eax,questId
        call u0x47A5D0
    }
}
