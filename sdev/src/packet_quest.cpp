#include <util/util.h>
#include <shaiya/include/network/game/outgoing/0900.h>
#include <shaiya/include/network/gameLog/incoming/0500.h>
#include "include/main.h"
#include "include/shaiya/CQuest.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/ItemInfo.h"
#include "include/shaiya/NetworkHelper.h"
#include "include/shaiya/QuestInfo.h"
using namespace shaiya;

namespace packet_quest
{
    /// <summary>
    /// Sends packet 0x903 (6.0) failure packet to the user.
    /// </summary>
    void send_failure_0x903(CUser* user, CQuest* quest, unsigned npcId)
    {
        GameQuestEndOutgoing_EP6 outgoing{};
        outgoing.npcId = npcId;
        outgoing.questId = quest->info->questId;
        outgoing.success = false;
        NetworkHelper::Send(user, &outgoing, sizeof(GameQuestEndOutgoing_EP6));
    }

    /// <summary>
    /// Sends the 0x903 (6.0) success packet to the user.
    /// </summary>
    void send_success_0x903(CUser* user, CQuest* quest, unsigned npcId, int resultIndex)
    {
        if (resultIndex >= QuestResultCount_EP6)
            return;

        auto& result = quest->info->results[resultIndex];
        if (result.exp)
        {
            CUser::AddExpFromUser(user, 0, result.exp, true);
        }

        if (result.money)
        {
            CUser::ChkAddMoneyGet(user, result.money);
            CUser::SendDBMoney(user);
        }

        GameLogQuestEndIncoming gameLog{};
        CUser::SetGameLogMain(user, &gameLog.packet);
        gameLog.packet.questId = quest->info->questId;
        std::memcpy(gameLog.packet.questName.data(), quest->info->questName.data(), gameLog.packet.questName.size());
        gameLog.packet.success = true;
        gameLog.packet.money = result.money;

        GameQuestEndOutgoing_EP6 outgoing{};
        outgoing.npcId = npcId;
        outgoing.questId = quest->info->questId;
        outgoing.success = true;
        outgoing.resultIndex = resultIndex;
        outgoing.exp = result.exp;
        outgoing.money = result.money;

        auto it = result.itemList.cbegin();
        auto last = result.itemList.cend();
        auto dest = outgoing.itemList.begin();

        for (; it != last; ++it, ++dest)
        {
            int bag{}, slot{}; ItemInfo itemInfo{};
            if (CUser::QuestAddItem(user, it->type, it->typeId, it->count, &bag, &slot, &itemInfo))
            {
                dest->count = it->count;
                dest->bag = bag;
                dest->slot = slot;
                dest->type = it->type;
                dest->typeId = it->typeId;

                gameLog.packet.itemId = itemInfo.itemId;
                gameLog.packet.itemCount = it->count;
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
    // esi = success boolean
    __asm
    {
        // original
        mov ecx,[esp+0xE0]
        xor esi,esi

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
