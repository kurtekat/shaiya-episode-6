#include <ranges>
#pragma warning(disable: 28159) // GetTickCount
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common/ItemEffect.h>
#include <shaiya/include/SConnection.h>
#include "include/shaiya/include/Helpers.h"
#include "include/shaiya/include/CClientToDBAgent.h"
#include "include/shaiya/include/CClientToGameLog.h"
#include "include/shaiya/include/CClientToMgr.h"
#include "include/shaiya/include/CGameData.h"
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CLogConnection.h"
#include "include/shaiya/include/CObjectMgr.h"
#include "include/shaiya/include/CSkill.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/CWorld.h"
#include "include/shaiya/include/SConnectionTBaseReconnect.h"
#include "include/shaiya/include/network/dbAgent/incoming/0600.h"
#include "include/shaiya/include/network/dbAgent/incoming/0700.h"
#include "include/shaiya/include/network/game/outgoing/0200.h"
#include "include/shaiya/include/network/game/outgoing/1100.h"
#include "include/shaiya/include/network/game/outgoing/F900.h"
#include "include/shaiya/include/network/gameLog/incoming/0400.h"
using namespace shaiya;

int Helpers::GetFreeItemSlot(CUser* user, uint8_t bag)
{
    if (!bag || bag > user->bagsUnlocked)
        return -1;

    for (int slot = 0; slot < max_inventory_slot; ++slot)
    {
        if (!user->inventory[bag][slot])
            return slot;
    }

    return -1;
}

bool Helpers::ItemRemove(CUser* user, uint8_t bag, uint8_t slot, uint8_t count)
{
    if (!bag || bag >= user->inventory.size() || slot >= max_inventory_slot)
        return false;

    auto& item = user->inventory[bag][slot];
    if (!item)
        return false;

    if (item->count < count)
        return false;

    item->count -= count;

    DBAgentItemRemoveIncoming packet(user->userId, bag, slot, count);
    Helpers::SendDBAgent(&packet, sizeof(DBAgentItemRemoveIncoming));

    GameLogItemRemoveIncoming gameLog(user, item, bag, slot, count);
    Helpers::SendGameLog(&gameLog, sizeof(GameLogItemRemoveIncoming));

    if (!item->count)
    {
        ItemRemoveOutgoing outgoing(bag, slot, 0, 0, 0);
        SConnection::Send(&user->connection, &outgoing, sizeof(ItemRemoveOutgoing));

        CObjectMgr::FreeItem(item);
        user->inventory[bag][slot] = nullptr;
    }
    else
    {
        ItemRemoveOutgoing outgoing(bag, slot, item->type, item->typeId, item->count);
        SConnection::Send(&user->connection, &outgoing, sizeof(ItemRemoveOutgoing));
    }

    return true;
}

bool Helpers::ItemRemove(CUser* user, uint32_t itemId, uint8_t count)
{
    for (const auto& [bag, items] : std::views::enumerate(
        std::as_const(user->inventory)))
    {
        if (!bag)
            continue;

        for (const auto& [slot, item] : std::views::enumerate(
            std::as_const(items)))
        {
            if (!item)
                continue;

            if (item->itemInfo->itemId != itemId)
                continue;

            if (item->count < count)
                continue;

            if (ItemRemove(user, bag, slot, count))
                return true;
        }
    }

    return false;
}

bool Helpers::ItemRemove(CUser* user, ItemEffect effect, uint8_t count)
{
    for (const auto& [bag, items] : std::views::enumerate(
        std::as_const(user->inventory)))
    {
        if (!bag)
            continue;

        for (const auto& [slot, item] : std::views::enumerate(
            std::as_const(items)))
        {
            if (!item)
                continue;

            if (item->itemInfo->effect != effect)
                continue;

            if (item->count < count)
                continue;

            if (ItemRemove(user, bag, slot, count))
                return true;
        }
    }

    return false;
}

bool Helpers::HasApplySkill(CUser* user, int skillId, int skillLv)
{
    EnterCriticalSection(&user->applySkills.cs);

    auto node = user->applySkills.sentinel.tail;
    node = node->next;
    user->applySkills.sentinel.head = node;

    while (node && node != user->applySkills.sentinel.tail)
    {
        auto skill = reinterpret_cast<CSkill*>(node);
        if (skill->skillId == skillId && skill->skillLv == skillLv)
        {
            LeaveCriticalSection(&user->applySkills.cs);
            return true;
        }

        node = user->applySkills.sentinel.head;
        node = node->next;
        user->applySkills.sentinel.head = node;
    }

    LeaveCriticalSection(&user->applySkills.cs);
    return false;
}

void Helpers::SendMessageToServer(CUser* sender, const char* message)
{
    ChatMessageToServerOutgoing outgoing(sender->charName.data(), message);
    CWorld::SendAll(&outgoing, outgoing.length());
}

void Helpers::SendMessageToServer(const char* senderName, const char* message)
{
    ChatMessageToServerOutgoing outgoing(senderName, message);
    CWorld::SendAll(&outgoing, outgoing.length());
}

void Helpers::SendNotice(const char* message)
{
    AdminCmdNoticeAllOutgoing outgoing(message);
    CWorld::SendAll(&outgoing, outgoing.length());
}

void Helpers::SendNoticeTo(CUser* user, const char* message)
{
    AdminCmdNoticeToOutgoing outgoing(message);
    SConnection::Send(&user->connection, &outgoing, outgoing.length());
}

void Helpers::SendNoticeTo(uint32_t charId, const char* message)
{
    auto user = CWorld::FindUser(charId);
    if (!user)
        return;

    AdminCmdNoticeToOutgoing outgoing(message);
    SConnection::Send(&user->connection, &outgoing, outgoing.length());
}

void Helpers::SendNoticeTo(const char* charName, const char* message)
{
    auto user = CWorld::FindUser(charName);
    if (!user)
        return;

    AdminCmdNoticeToOutgoing outgoing(message);
    SConnection::Send(&user->connection, &outgoing, outgoing.length());
}

void Helpers::SendDBAgent(void* buf, int len)
{
    SConnectionTBaseReconnect::Send(&g_pClientToDBAgent->connection, buf, len);
}

void Helpers::SendGameLog(void* buf, int len)
{
    SConnectionTBaseReconnect::Send(&g_pClientToGameLog->connection, buf, len);
}

void Helpers::SendSession(void* buf, int len)
{
    SConnectionTBaseReconnect::Send(&g_pClientToMgr->connection, buf, len);
}

void Helpers::SendUserLog(void* buf, int len)
{
    SConnectionTBaseReconnect::Send(&g_pClientToLog->connection, buf, len);
}

bool Helpers::SetMovePosition(CUser* user, int mapId, float x, float y, float z, int recallType, ULONG delay)
{
    if (user->status == UserStatus::Death || user->where != UserWhere::ZoneEnter)
        return false;

    user->recallMapId = mapId;
    user->recallPos.x = x;
    user->recallPos.y = y;
    user->recallPos.z = z;
    user->recallType = UserRecallType(recallType);
    user->recallTick = GetTickCount() + delay;
    return true;
}

bool Helpers::SetMovePosition(CUser* user, int mapId, SVector* pos, int recallType, ULONG delay)
{
    return Helpers::SetMovePosition(user, mapId, pos->x, pos->y, pos->z, recallType, delay);
}
