#include <ranges>
#include <string>
#pragma warning(disable: 28159) // GetTickCount
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common.h>
#include <shaiya/include/common/ItemTypes.h>
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
#include "include/shaiya/include/NetworkHelper.h"
#include "include/shaiya/include/SConnection.h"
#include "include/shaiya/include/SConnectionTBaseReconnect.h"
#include "include/shaiya/include/UserHelper.h"
#include "include/shaiya/include/network/dbAgent/incoming/0600.h"
#include "include/shaiya/include/network/dbAgent/incoming/0700.h"
#include "include/shaiya/include/network/game/outgoing/0200.h"
#include "include/shaiya/include/network/gameLog/incoming/0400.h"
using namespace shaiya;

bool UserHelper::HasApplySkill(CUser* user, int skillId, int skillLv)
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

bool UserHelper::ItemCreate(CUser* user, ItemInfo* itemInfo, int count, int& outBag, int& outSlot)
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

bool UserHelper::ItemRemove(CUser* user, int bag, int slot, int count)
{
    if (!bag || bag >= int(user->inventory.size()) || slot >= max_inventory_slot)
        return false;

    auto& item = user->inventory[bag][slot];
    if (!item)
        return false;

    if (item->count < count)
        return false;

    item->count -= count;

    DBAgentItemRemoveIncoming packet(user->userId, bag, slot, count);
    NetworkHelper::SendDBAgent(&packet, sizeof(DBAgentItemRemoveIncoming));

    GameLogItemRemoveIncoming gameLog(user, item, bag, slot, count);
    NetworkHelper::SendGameLog(&gameLog, sizeof(GameLogItemRemoveIncoming));

    if (!item->count)
    {
        ItemRemoveOutgoing outgoing(bag, slot, 0, 0, 0);
        NetworkHelper::Send(user, &outgoing, sizeof(ItemRemoveOutgoing));

        CObjectMgr::FreeItem(item);
        user->inventory[bag][slot] = nullptr;
    }
    else
    {
        ItemRemoveOutgoing outgoing(bag, slot, item->type, item->typeId, item->count);
        NetworkHelper::Send(user, &outgoing, sizeof(ItemRemoveOutgoing));
    }

    return true;
}

bool UserHelper::ItemRemove(CUser* user, ItemId itemId, int count)
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

bool UserHelper::ItemRemove(CUser* user, ItemEffect effect, int count)
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

void UserHelper::SetMovePosition(CUser* user, int mapId, float x, float y, float z, int recallType, ULONG delay)
{
    user->recallMapId = mapId;
    user->recallPos.x = x;
    user->recallPos.y = y;
    user->recallPos.z = z;
    user->recallType = UserRecallType(recallType);
    user->recallTick = GetTickCount() + delay;
}

void UserHelper::SetMovePosition(CUser* user, int mapId, SVector* pos, int recallType, ULONG delay)
{
    UserHelper::SetMovePosition(user, mapId, pos->x, pos->y, pos->z, recallType, delay);
}

bool UserHelper::Teleport(CUser* user, int mapId, float x, float y, float z, int recallType, ULONG delay)
{
    if (user->status == UserStatus::Death || user->where != UserWhere::ZoneEnter)
        return false;

    if (!user->connection.object.zone)
        return false;

    if (!CWorld::GetZone(mapId))
        return false;

    CUser::CancelActionExc(user);
    MyShop::Ended(&user->myShop);
    UserHelper::SetMovePosition(user, mapId, x, y, z, recallType, delay);
    return true;
}

bool UserHelper::Teleport(CUser* user, int mapId, SVector* pos, int recallType, ULONG delay)
{
    return UserHelper::Teleport(user, mapId, pos->x, pos->y, pos->z, recallType, delay);
}
