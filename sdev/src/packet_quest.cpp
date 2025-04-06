#include <strsafe.h>
#include <util/util.h>
#include <shaiya/include/network/game/outgoing/0900.h>
#include <shaiya/include/network/gameLog/incoming/0500.h>
#include "include/main.h"
#include "include/shaiya/include/CQuest.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/ItemInfo.h"
#include "include/shaiya/include/NetworkHelper.h"
#include "include/shaiya/include/QuestInfo.h"
using namespace shaiya;

namespace packet_quest
{
    /// <summary>
    /// Sends packet 0x903 (6.0) failure packet to the user.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="quest"></param>
    /// <param name="npcId"></param>
    void send_failure_0x903(CUser* user, CQuest* quest, uint npcId)
    {
        GameQuestEndOutgoing_EP6 outgoing{};
        outgoing.npcId = npcId;
        outgoing.questId = quest->info->questId;
        outgoing.success = false;
        NetworkHelper::Send(user, &outgoing, sizeof(GameQuestEndOutgoing_EP6));
    }

    /// <summary>
    /// Sends the 0x903 (6.0) success packet to the user. Adds support for skill ability 87. 
    /// Please note that the client does not prevent gold overflow when it handles the 0x903 
    /// packet. Do not report it.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="quest"></param>
    /// <param name="npcId"></param>
    /// <param name="resultIndex"></param>
    void send_success_0x903(CUser* user, CQuest* quest, uint npcId, int resultIndex)
    {
        auto questInfo = quest->info;
        if (std::cmp_greater_equal(resultIndex, questInfo->results.size()))
            return;

        auto exp = questInfo->results[resultIndex].exp;
        if (exp)
        {
            auto rate = user->multiplyQuestExpRate;
            if (rate >= 200)
                exp *= rate / 100;

            CUser::AddExpFromUser(user, 0, exp, true);
        }

        auto gold = questInfo->results[resultIndex].gold;
        if (gold)
        {
            CUser::ChkAddMoneyGet(user, gold);
            CUser::SendDBMoney(user);
        }

        GameLogQuestEndIncoming gameLog{};
        CUser::SetGameLogMain(user, &gameLog.packet);
        gameLog.packet.questId = questInfo->questId;
        StringCbCopyA(gameLog.packet.questName.data(), gameLog.packet.questName.size(), questInfo->questName.data());
        gameLog.packet.success = true;
        gameLog.packet.gold = gold;

        GameQuestEndOutgoing_EP6 outgoing{};
        outgoing.npcId = npcId;
        outgoing.questId = questInfo->questId;
        outgoing.success = true;
        outgoing.resultIndex = resultIndex;
        outgoing.exp = exp;
        outgoing.gold = gold;

        auto& itemList = questInfo->results[resultIndex].itemList;
        for (int i = 0; std::cmp_less(i, itemList.size()); ++i)
        {
            int type = itemList[i].type;
            int typeId = itemList[i].typeId;
            int count = itemList[i].count;

            int bag{}, slot{};
            ItemInfo itemInfo{};
            if (CUser::QuestAddItem(user, type, typeId, count, &bag, &slot, &itemInfo))
            {
                outgoing.itemList[i].count = count;
                outgoing.itemList[i].bag = bag;
                outgoing.itemList[i].slot = slot;
                outgoing.itemList[i].type = type;
                outgoing.itemList[i].typeId = typeId;

                gameLog.packet.itemId = itemInfo.itemId;
                gameLog.packet.itemCount = count;
                gameLog.packet.itemName = itemInfo.itemName;
            }
            else
            {
                outgoing.itemList[i].count = 0;
                outgoing.itemList[i].bag = 0;
                outgoing.itemList[i].slot = 0;
                outgoing.itemList[i].type = 0;
                outgoing.itemList[i].typeId = 0;

                gameLog.packet.itemId = 0;
                gameLog.packet.itemCount = 0;
                gameLog.packet.itemName = {};
            }

            NetworkHelper::SendGameLog(&gameLog, sizeof(GameLogQuestEndIncoming));
        }

        NetworkHelper::Send(user, &outgoing, sizeof(GameQuestEndOutgoing_EP6));
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
        call packet_quest::send_failure_0x903
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
        call packet_quest::send_failure_0x903
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
        call packet_quest::send_success_0x903
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
