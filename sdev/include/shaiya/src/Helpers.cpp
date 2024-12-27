#include <ranges>
#pragma warning(disable: 28159) // GetTickCount
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common/ItemEffect.h>
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
#include "include/shaiya/include/SConnection.h"
#include "include/shaiya/include/SConnectionTBaseReconnect.h"
#include "include/shaiya/include/network/dbAgent/incoming/0600.h"
#include "include/shaiya/include/network/dbAgent/incoming/0700.h"
#include "include/shaiya/include/network/game/outgoing/0200.h"
#include "include/shaiya/include/network/game/outgoing/1100.h"
#include "include/shaiya/include/network/game/outgoing/F900.h"
#include "include/shaiya/include/network/gameLog/incoming/0400.h"
using namespace shaiya;

bool Helpers::ItemCreate(CUser* user, ItemInfo* itemInfo, int count, int& outBag, int& outSlot)
{
    if (count > itemInfo->count)
        return false;

    outBag = 1;
    while (std::cmp_less_equal(outBag, user->bagsUnlocked))
    {
        for (outSlot = 0; outSlot < max_inventory_slot; ++outSlot)
        {
            if (!user->inventory[outBag][outSlot])
                return CUser::ItemCreate(user, itemInfo, count);
        }

        ++outBag;
    }

    return false;
}

bool Helpers::ItemRemove(CUser* user, int bag, int slot, int count)
{
    if (!bag || bag > 5 || slot >= max_inventory_slot)
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
        Helpers::Send(user, &outgoing, sizeof(ItemRemoveOutgoing));

        CObjectMgr::FreeItem(item);
        user->inventory[bag][slot] = nullptr;
    }
    else
    {
        ItemRemoveOutgoing outgoing(bag, slot, item->type, item->typeId, item->count);
        Helpers::Send(user, &outgoing, sizeof(ItemRemoveOutgoing));
    }

    return true;
}

bool Helpers::ItemRemove(CUser* user, ItemId itemId, int count)
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

bool Helpers::ItemRemove(CUser* user, ItemEffect effect, int count)
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
    Helpers::Send(user, &outgoing, outgoing.length());
}

void Helpers::SendNoticeTo(uint32_t charId, const char* message)
{
    auto user = CWorld::FindUser(charId);
    if (!user)
        return;

    AdminCmdNoticeToOutgoing outgoing(message);
    Helpers::Send(user, &outgoing, outgoing.length());
}

void Helpers::SendNoticeTo(const char* charName, const char* message)
{
    auto user = CWorld::FindUser(charName);
    if (!user)
        return;

    AdminCmdNoticeToOutgoing outgoing(message);
    Helpers::Send(user, &outgoing, outgoing.length());
}

void Helpers::Send(CUser* user, void* packet, int length)
{
    SConnection::Send(&user->connection.connection, packet, length);
}

void Helpers::SendDBAgent(void* packet, int length)
{
    SConnectionTBaseReconnect::Send(&g_pClientToDBAgent->connection, packet, length);
}

void Helpers::SendGameLog(void* packet, int length)
{
    SConnectionTBaseReconnect::Send(&g_pClientToGameLog->connection, packet, length);
}

void Helpers::SendSession(void* packet, int length)
{
    SConnectionTBaseReconnect::Send(&g_pClientToMgr->connection, packet, length);
}

void Helpers::SendUserLog(void* packet, int length)
{
    SConnectionTBaseReconnect::Send(&g_pClientToLog->connection, packet, length);
}

void Helpers::SetMovePosition(CUser* user, int mapId, float x, float y, float z, int recallType, ULONG delay)
{
    user->recallMapId = mapId;
    user->recallPos.x = x;
    user->recallPos.y = y;
    user->recallPos.z = z;
    user->recallType = RecallType(recallType);
    user->recallTick = GetTickCount() + delay;
}

void Helpers::SetMovePosition(CUser* user, int mapId, SVector* pos, int recallType, ULONG delay)
{
    Helpers::SetMovePosition(user, mapId, pos->x, pos->y, pos->z, recallType, delay);
}

bool Helpers::Teleport(CUser* user, int mapId, float x, float y, float z, int recallType, ULONG delay)
{
    if (user->status == CUser::Status::Death || user->where != CUser::Where::ZoneEnter)
        return false;

    if (!user->connection.object.zone)
        return false;

    if (!CWorld::GetZone(mapId))
        return false;

    CUser::CancelActionExc(user);
    MyShop::Ended(&user->myShop);
    Helpers::SetMovePosition(user, mapId, x, y, z, recallType, delay);
    return true;
}

bool Helpers::Teleport(CUser* user, int mapId, SVector* pos, int recallType, ULONG delay)
{
    return Helpers::Teleport(user, mapId, pos->x, pos->y, pos->z, recallType, delay);
}
