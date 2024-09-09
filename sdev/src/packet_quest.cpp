#include <strsafe.h>
#include <shaiya/include/SConnection.h>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CQuest.h"
#include "include/shaiya/include/CQuestData.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/Helpers.h"
#include "include/shaiya/include/ItemInfo.h"
#include "include/shaiya/include/network/game/outgoing/0900.h"
#include "include/shaiya/include/network/gameLog/incoming/0500.h"
using namespace shaiya;

namespace packet_quest
{
    void send_failure_result(CUser* user, CQuest* quest, uint32_t npcId)
    {
        QuestEndResultOutgoing outgoing{};
        outgoing.npcId = npcId;
        outgoing.questId = quest->questInfo->questId;
        SConnection::Send(&user->connection, &outgoing, sizeof(QuestEndResultOutgoing));
    }

    void send_success_result(CUser* user, CQuest* quest, uint32_t npcId, uint8_t index)
    {
        if (index >= quest->questInfo->results.size())
            return;

        auto exp = quest->questInfo->results[index].exp;
        auto gold = quest->questInfo->results[index].gold;

        if (exp)
        {
            auto rate = user->skillAbility.increaseQuestExpRate;
            exp = (rate >= 200) ? exp * (rate / 100) : exp;
            CUser::AddExpFromUser(user, 0, exp, true);
        }

        if (gold)
        {
            CUser::ChkAddMoneyGet(user, gold);
            CUser::SendDBMoney(user);
        }

        GameLogQuestEndResultIncoming gameLog{};
        CUser::SetGameLogMain(user, &gameLog);
        gameLog.questId = quest->questInfo->questId;
        StringCbCopyA(gameLog.questName.data(), gameLog.questName.size(), quest->questInfo->questName.data());
        gameLog.success = true;
        gameLog.gold = gold;

        QuestEndResultOutgoing outgoing{};
        outgoing.npcId = npcId;
        outgoing.questId = quest->questInfo->questId;
        outgoing.success = true;
        outgoing.index = index;
        outgoing.exp = exp;
        outgoing.gold = gold;

#ifdef SHAIYA_EP6_4_PT
        auto& items = quest->questInfo->results[index].items;
        for (int i = 0; std::cmp_less(i, items.size()); ++i)
        {
            int type = items[i].type;
            int typeId = items[i].typeId;
            int count = items[i].count;

            int bag{}, slot{};
            ItemInfo itemInfo{};
            if (CUser::QuestAddItem(user, type, typeId, count, &bag, &slot, &itemInfo))
            {
                outgoing.itemList[i].count = count;
                outgoing.itemList[i].bag = bag;
                outgoing.itemList[i].slot = slot;
                outgoing.itemList[i].type = type;
                outgoing.itemList[i].typeId = typeId;

                gameLog.itemId = itemInfo.itemId;
                gameLog.itemCount = count;
                gameLog.itemName = itemInfo.itemName;
            }
            else
            {
                outgoing.itemList[i].count = 0;
                outgoing.itemList[i].bag = 0;
                outgoing.itemList[i].slot = 0;
                outgoing.itemList[i].type = 0;
                outgoing.itemList[i].typeId = 0;

                gameLog.itemId = 0;
                gameLog.itemCount = 0;
                gameLog.itemName[0] = '\0';
            }

            Helpers::SendGameLog(&gameLog, sizeof(GameLogQuestEndResultIncoming));
        }
#endif

        SConnection::Send(&user->connection, &outgoing, sizeof(QuestEndResultOutgoing));
        CUser::QuestRemove(user, quest, true);
    }
}

unsigned u0x48D237 = 0x48D237;
void __declspec(naked) naked_0x48D1F2()
{
    __asm
    {
        pushad

        push 0x0 // npcId
        push ebp // quest
        push ebx // user
        call packet_quest::send_failure_result
        add esp,0xC

        popad

        jmp u0x48D237
    }
}

unsigned u0x48DC91 = 0x48DC91;
void __declspec(naked) naked_0x48DC3D()
{
    __asm
    {
        // original
        mov ecx,[esp+0xE0]

        pushad

        push ecx // npcId
        push ebx // quest
        push edi // user
        call packet_quest::send_failure_result
        add esp,0xC

        popad

        jmp u0x48DC91
    }
}

unsigned u0x48E029 = 0x48E029;
void __declspec(naked) naked_0x48DE38()
{
    __asm
    {
        pushad

        mov ecx,[esp+0x114]

        push edx // index
        push ecx // npcId
        push ebx // quest
        push edi // user
        call packet_quest::send_success_result
        add esp,0x10

        popad

        jmp u0x48E029
    }
}

void hook::packet_quest()
{
    // CUser::QuestRemoveAdmin
    util::detour((void*)0x48D1F2, naked_0x48D1F2, 9);
    // CUser::QuestEnd
    util::detour((void*)0x48DC3D, naked_0x48DC3D, 11);
    // CUser::QuestSuccessResult
    util::detour((void*)0x48DE38, naked_0x48DE38, 5);
}
