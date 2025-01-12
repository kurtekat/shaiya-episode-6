#include <strsafe.h>
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
    /// <summary>
    /// Sends packet 0x903 (6.4) to the user, which indicates failure.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="quest"></param>
    /// <param name="npcId"></param>
    void send_failure_result(CUser* user, CQuest* quest, ULONG npcId)
    {
        QuestEndResultOutgoing_EP6 outgoing(npcId, quest->questInfo->questId, false, 0, 0, 0, {});
        Helpers::Send(user, &outgoing, sizeof(QuestEndResultOutgoing_EP6));
    }

    /// <summary>
    /// Sends the episode 6.0 quest success result. Adds support for skill ability 87. Please note that 
    /// the client does not prevent gold overflow when it handles the 0x903 packet.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="quest"></param>
    /// <param name="questInfo"></param>
    /// <param name="npcId"></param>
    /// <param name="index"></param>
    void send_success_result(CUser* user, CQuest* quest, QuestInfo_EP6* questInfo, ULONG npcId, int index)
    {
        if (index >= int(questInfo->results.size()))
            return;

        auto exp = questInfo->results[index].exp;
        if (exp)
        {
            auto rate = user->skillAbility.multiplyQuestExpRate;
            if (rate >= 200)
                exp *= rate / 100;

            CUser::AddExpFromUser(user, 0, exp, true);
        }

        auto gold = questInfo->results[index].gold;
        if (gold)
        {
            CUser::ChkAddMoneyGet(user, gold);
            CUser::SendDBMoney(user);
        }

        GameLogQuestEndResultIncoming gameLog{};
        CUser::SetGameLogMain(user, &gameLog);
        StringCbCopyA(gameLog.questName.data(), gameLog.questName.size(), questInfo->questName.data());
        gameLog.success = true;
        gameLog.gold = gold;

        QuestEndResultOutgoing_EP6 outgoing(npcId, questInfo->questId, true, index, exp, gold, {});

        auto& items = questInfo->results[index].items;
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
                gameLog.itemName = {};
            }

            Helpers::SendGameLog(&gameLog, sizeof(GameLogQuestEndResultIncoming));
        }

        Helpers::Send(user, &outgoing, sizeof(QuestEndResultOutgoing_EP6));
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
        push eax // questInfo
        push ebx // quest
        push edi // user
        call packet_quest::send_success_result
        add esp,0x14

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
