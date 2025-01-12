#pragma once
#include <strsafe.h>
#include <shaiya/include/common.h>
#include <shaiya/include/common/QuestTypes.h>
#include "include/shaiya/include/CQuestData.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/GameLogMain.h"

namespace shaiya
{
    #pragma pack(push, 1)
    // ActionType 133
    struct GameLogQuestEndResultIncoming
    {
        UINT16 opcode{ 0x502 };
        GameLogMain main;
        UINT16 questId;
        QuestName questName;
        bool success;
        UINT32 gold;
        UINT32 itemId;
        UINT8 itemCount;
        ItemName itemName;

        GameLogQuestEndResultIncoming() = default;

        GameLogQuestEndResultIncoming(CUser* user, QuestInfo* questInfo, bool success, UINT32 gold, UINT32 itemId, 
            UINT8 itemCount, const ItemName& itemName)
            : main{}, questName{}, itemName{}
        {
            CUser::SetGameLogMain(user, this);
            this->questId = questInfo->questId;
            this->questName = questInfo->questName;
            this->success = success;
            this->gold = gold;
            this->itemId = itemId;
            this->itemCount = itemCount;
            this->itemName = itemName;
        }
    };
    #pragma pack(pop)
}
