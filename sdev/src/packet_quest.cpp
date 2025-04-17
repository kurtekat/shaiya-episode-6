#include <ranges>
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
    void send_success_0x903(CUser* user, CQuest* quest, uint npcId, uint resultIndex)
    {
        if (resultIndex >= quest->info->results.size())
            return;

        auto exp = quest->info->results[resultIndex].exp;
        auto money = quest->info->results[resultIndex].money;

        if (exp)
        {
            auto rate = user->multiplyQuestExpRate;
            if (rate >= 200)
                exp *= rate / 100;

            CUser::AddExpFromUser(user, 0, exp, true);
        }

        if (money)
        {
            CUser::ChkAddMoneyGet(user, money);
            CUser::SendDBMoney(user);
        }

        GameLogQuestEndIncoming gameLog{};
        CUser::SetGameLogMain(user, &gameLog.packet);
        gameLog.packet.questId = quest->info->questId;
        std::memcpy(gameLog.packet.questName.data(), quest->info->questName.data(), gameLog.packet.questName.size());
        gameLog.packet.success = true;
        gameLog.packet.money = money;

        GameQuestEndOutgoing_EP6 outgoing{};
        outgoing.npcId = npcId;
        outgoing.questId = quest->info->questId;
        outgoing.success = true;
        outgoing.resultIndex = resultIndex;
        outgoing.exp = exp;
        outgoing.money = money;

        for (auto&& [unit, item] : std::views::zip(
            outgoing.itemList,
            std::as_const(quest->info->results[resultIndex].itemList)))
        {
            int bag{}, slot{};
            ItemInfo itemInfo{};
            if (CUser::QuestAddItem(user, item.type, item.typeId, item.count, &bag, &slot, &itemInfo))
            {
                unit.count = item.count;
                unit.bag = bag;
                unit.slot = slot;
                unit.type = item.type;
                unit.typeId = item.typeId;

                gameLog.packet.itemId = itemInfo.itemId;
                gameLog.packet.itemCount = item.count;
                gameLog.packet.itemName = itemInfo.itemName;
            }
            else
            {
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
