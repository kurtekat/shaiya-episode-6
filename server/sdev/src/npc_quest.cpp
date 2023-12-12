#include <memory>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>
#include <include/shaiya/packets/0200.h>
#include <include/shaiya/packets/0900.h>
#include <include/shaiya/include/CGameData.h>
#include <include/shaiya/include/CItem.h>
#include <include/shaiya/include/CQuest.h>
#include <include/shaiya/include/CQuestData.h>
#include <include/shaiya/include/CUser.h>
#include <include/shaiya/include/SConnection.h>
#include <include/shaiya/include/ServerTime.h>
using namespace shaiya;

namespace npc_quest
{
    void send_admin_remove(CUser* user, CQuest* quest)
    {
        QuestEndResultOutgoing packet{};
        packet.questId = quest->id;
        SConnection::Send(&user->connection, &packet, sizeof(QuestEndResultOutgoing));
    }

    void send_failure_result(CUser* user, CQuest* quest, ULONG npcId)
    {
        QuestEndResultOutgoing packet{};
        packet.npcId = npcId;
        packet.questId = quest->id;
        SConnection::Send(&user->connection, &packet, sizeof(QuestEndResultOutgoing));
    }

    void send_success_result(CUser* user, CQuest* quest, Packet buffer)
    {
        auto npcId = util::read_bytes<std::uint32_t>(buffer, 2);
        auto index = util::read_bytes<std::uint8_t>(buffer, 9);

        if (index >= quest->questInfo->result.size())
        {
            send_failure_result(user, quest, npcId);
            return;
        }

        QuestEndResultOutgoing packet{};
        packet.npcId = npcId;
        packet.questId = quest->id;
        packet.success = true;
        packet.index = index;

        auto& result = quest->questInfo->result[index];

        packet.exp = result.exp;
        packet.gold = result.gold;

        #ifdef SHAIYA_EP6_QUEST_RESULT
        for (std::size_t i = 0; i < result.item.size(); ++i)
        {
            int type = result.item[i].type;
            int typeId = result.item[i].typeId;
            int count = result.item[i].count;

            int bag, slot;
            auto itemInfo = std::make_unique<CGameData::ItemInfo*>();
            if (CUser::QuestAddItem(user, type, typeId, count, &bag, &slot, itemInfo.get()))
            {
                packet.itemList[i].count = count;
                packet.itemList[i].bag = bag;
                packet.itemList[i].slot = slot;
                packet.itemList[i].type = type;
                packet.itemList[i].typeId = typeId;
            }
        }
        #endif

        SConnection::Send(&user->connection, &packet, sizeof(QuestEndResultOutgoing));

        #if defined SHAIYA_EP6_QUEST_RESULT && defined SHAIYA_EP6_ITEM_DURATION
        for (const auto& item0903 : packet.itemList)
        {
            auto itemInfo = CGameData::GetItemInfo(item0903.type, item0903.typeId);
            if (!itemInfo)
                continue;

            if (ServerTime::IsTimedItem(itemInfo))
            {
                ItemDurationOutgoing packet{};
                packet.bag = item0903.bag;
                packet.slot = item0903.slot;
                packet.fromDate = ServerTime::GetSystemTime();
                packet.toDate = ServerTime::GetExpireTime(packet.fromDate, itemInfo->range);
                SConnection::Send(&user->connection, &packet, sizeof(ItemDurationOutgoing));
            }
        }
        #endif
    }
}

unsigned u0x48D237 = 0x48D237;
void __declspec(naked) naked_0x48D1F2()
{
    __asm
    {
        pushad

        push ebp // quest
        push ebx // user
        call npc_quest::send_admin_remove
        add esp,0x8

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
        call npc_quest::send_failure_result
        add esp,0xC

        popad

        jmp u0x48DC91
    }
}

unsigned u0x48E009 = 0x48E009;
void __declspec(naked) naked_0x48DF4A()
{
    __asm
    {
        lea edx,[esp+0x10]

        pushad

        push edx // packet
        push ebx // quest
        push edi // user
        call npc_quest::send_success_result
        add esp,0xC

        popad

        jmp u0x48E009
    }
}

void hook::npc_quest()
{
    // CUser::QuestRemoveAdmin
    util::detour((void*)0x48D1F2, naked_0x48D1F2, 9);
    // CUser::QuestEnd
    util::detour((void*)0x48DC3D, naked_0x48DC3D, 11);
    // CUser::QuestSuccessResult
    util::detour((void*)0x48DF4A, naked_0x48DF4A, 7);
}
