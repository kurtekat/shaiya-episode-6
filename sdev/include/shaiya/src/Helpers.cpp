#include <ranges>
#include <shaiya/include/common/SConnection.h>
#include <shaiya/include/item/ItemEffect.h>
#include <shaiya/include/network/dbAgent/incoming/0700.h>
#include <shaiya/include/network/game/outgoing/0200.h>
#include <shaiya/include/network/game/outgoing/F900.h>
#include <shaiya/include/network/gameLog/incoming/0400.h>
#include "include/shaiya/include/Helpers.h"
#include "include/shaiya/include/CClientToDBAgent.h"
#include "include/shaiya/include/CClientToGameLog.h"
#include "include/shaiya/include/CGameData.h"
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CObjectMgr.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/CWorld.h"
#include "include/shaiya/include/SConnectionTBaseReconnect.h"
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
    if (!bag || bag >= max_inventory_bag || slot >= max_inventory_slot)
        return false;

    auto& item = user->inventory[bag][slot];
    if (!item)
        return false;

    if (item->count < count)
        return false;

    item->count -= count;

    DBAgentItemRemoveIncoming packet(user->userId, bag, slot, count);
    SConnectionTBaseReconnect::Send(&g_pClientToDBAgent->connection, &packet, sizeof(DBAgentItemRemoveIncoming));

    GameLogItemRemoveIncoming log(user, item, bag, slot, count);
    SConnectionTBaseReconnect::Send(&g_pClientToGameLog->connection, &log, sizeof(GameLogItemRemoveIncoming));

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
