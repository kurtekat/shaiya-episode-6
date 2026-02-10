#pragma warning(disable: 28159) // GetTickCount
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common.h>
#include <shaiya/include/common/ItemEffect.h>
#include <shaiya/include/network/dbAgent/incoming/0600.h>
#include <shaiya/include/network/dbAgent/incoming/0700.h>
#include <shaiya/include/network/game/outgoing/0200.h>
#include <shaiya/include/network/gameLog/incoming/0400.h>
#include "CClientToDBAgent.h"
#include "CClientToGameLog.h"
#include "CClientToMgr.h"
#include "CGameData.h"
#include "ChaoticSquare.h"
#include "CItem.h"
#include "CLogConnection.h"
#include "CObjectMgr.h"
#include "CSkill.h"
#include "CUser.h"
#include "CWorld.h"
#include "ItemFinder.h"
#include "ItemInfo.h"
#include "ItemPredicate.h"
#include "Network.h"
#include "SConnection.h"
#include "SConnectionTBaseReconnect.h"
#include "UserHelper.h"
using namespace shaiya;

bool UserHelper::IsValidItemPosition(CUser* user, int bag, int slot)
{
    if (bag > user->bagsUnlocked)
        return false;

    if (slot >= 24)
        return false;

    return true;
}

bool UserHelper::ItemCreate(CUser* user, ItemInfo* itemInfo, int count, int& outBag, int& outSlot)
{
    if (count < 1 || count > itemInfo->count)
        return false;

    for (outBag = 1; outBag <= user->bagsUnlocked; ++outBag)
    {
        for (outSlot = 0; outSlot < 24; ++outSlot)
        {
            if (!user->inventory[outBag][outSlot])
                return CUser::ItemCreate(user, itemInfo, count);
        }
    }

    return false;
}

bool UserHelper::ItemRemove(CUser* user, int bag, int slot, int count)
{
    if (!UserHelper::IsValidItemPosition(user, bag, slot))
        return false;

    auto& item = user->inventory[bag][slot];
    if (!item)
        return false;

    if (count < 1 || count > item->count)
        return false;

    item->count -= count;

    DBAgentItemDropIncoming packet{};
    packet.billingId = user->billingId;
    packet.bag = bag;
    packet.slot = slot;
    packet.count = count;
    Network::SendDBAgent(&packet, sizeof(DBAgentItemDropIncoming));

    GameLogItemDropIncoming gameLog{};
    CUser::SetGameLogMain(user, &gameLog.packet);
    gameLog.packet.uniqueId = item->uniqueId;
    gameLog.packet.itemId = item->info->itemId;
    gameLog.packet.itemName = item->info->itemName;
    gameLog.packet.gems = item->gems;
    gameLog.packet.makeTime = item->makeTime;
    gameLog.packet.craftName = item->craftName;
    gameLog.packet.bag = bag;
    gameLog.packet.slot = slot;
    gameLog.packet.count = count;
    Network::SendGameLog(&gameLog.packet, sizeof(GameLogItemDropIncoming));

    if (!item->count)
    {
        GameItemDropOutgoing outgoing{};
        outgoing.bag = bag;
        outgoing.slot = slot;
        SConnection::Send(user, &outgoing, sizeof(GameItemDropOutgoing));

        CObjectMgr::FreeItem(item);
        user->inventory[bag][slot] = nullptr;
    }
    else
    {
        GameItemDropOutgoing outgoing{};
        outgoing.bag = bag;
        outgoing.slot = slot;
        outgoing.type = item->type;
        outgoing.typeId = item->typeId;
        outgoing.count = item->count;
        SConnection::Send(user, &outgoing, sizeof(GameItemDropOutgoing));
    }

    return true;
}

void UserHelper::SetMovePosition(CUser* user, unsigned mapId, float x, float y, float z, MoveType moveType, unsigned delay)
{
    user->moveMapId = mapId;
    user->movePos.x = x;
    user->movePos.y = y;
    user->movePos.z = z;
    user->moveType = moveType;
    user->moveTime = GetTickCount() + delay;
}

void UserHelper::SetMovePosition(CUser* user, unsigned mapId, SVector* pos, MoveType moveType, unsigned delay)
{
    UserHelper::SetMovePosition(user, mapId, pos->x, pos->y, pos->z, moveType, delay);
}

bool UserHelper::Move(CUser* user, unsigned mapId, float x, float y, float z, MoveType moveType, unsigned delay)
{
    if (user->status == UserStatus::Death || user->where != UserWhere::ZoneEnter)
        return false;

    if (!user->zone)
        return false;

    if (!CWorld::GetZone(mapId))
        return false;

    CUser::CancelActionExc(user);
    MyShop::Ended(&user->myShop);
    UserHelper::SetMovePosition(user, mapId, x, y, z, moveType, delay);
    return true;
}

bool UserHelper::Move(CUser* user, unsigned mapId, SVector* pos, MoveType moveType, unsigned delay)
{
    return UserHelper::Move(user, mapId, pos->x, pos->y, pos->z, moveType, delay);
}

bool UserHelper::RecipeRemove(CUser* user, const ChaoticSquareRecipe& recipe)
{
    for (int i = 0; i < 24; ++i)
    {
        auto type = recipe.materialType[i];
        auto typeId = recipe.materialTypeId[i];
        auto count = recipe.materialCount[i];

        if (!type || !typeId || !count)
            continue;

        int bag{}, slot{};
        if (!ItemFinder(user, bag, slot, ItemMinCountF(type, typeId, count)))
            return false;

        if (!UserHelper::ItemRemove(user, bag, slot, count))
            return false;
    }

    return true;
}
