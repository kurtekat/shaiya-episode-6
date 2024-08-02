#include <chrono>
#include <shaiya/include/common/SConnection.h>
#include <shaiya/include/network/dbAgent/incoming/0700.h>
#include <shaiya/include/network/game/outgoing/0200.h>
#include <shaiya/include/network/gameLog/incoming/0400.h>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CObjectMgr.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/Helpers.h"
#include "include/shaiya/include/ItemDuration.h"
#include "include/shaiya/include/ItemInfo.h"
#include "include/shaiya/include/ServerTime.h"
using namespace shaiya;

void ItemDuration::sendDeleteNotice(CUser* user, CItem* item, uint8_t bag, uint8_t slot)
{
    ItemExpireNoticeOutgoing outgoing{};
    outgoing.type = item->type;
    outgoing.typeId = item->typeId;

    if (bag == warehouse_bag)
    {
        outgoing.noticeType = ItemExpireNoticeType::DeletedFromWarehouse;

        DBAgentItemBankToBankIncoming packet(user->userId, slot, item->count, slot, 0);
        Helpers::SendDBAgent(&packet, sizeof(DBAgentItemBankToBankIncoming));

        GameLogItemRemoveIncoming log(user, item, bag, slot, item->count);
        Helpers::SendGameLog(&log, sizeof(GameLogItemRemoveIncoming));

        CObjectMgr::FreeItem(item);
        user->warehouse[slot] = nullptr;

        ItemBankToBankOutgoing outgoing{};
        outgoing.srcItem.bag = bag;
        outgoing.srcItem.slot = slot;
        outgoing.destItem.bag = bag;
        outgoing.destItem.slot = slot;
        SConnection::Send(&user->connection, &outgoing, sizeof(ItemBankToBankOutgoing));
    }
    else
    {
        outgoing.noticeType = ItemExpireNoticeType::DeletedFromInventory;
        CUser::ItemRemove(user, bag, slot);
    }

    SConnection::Send(&user->connection, &outgoing, sizeof(ItemExpireNoticeOutgoing));
}

void ItemDuration::sendExpireNotice(CUser* user, CItem* item, uint8_t bag, uint8_t slot)
{
    if (!item->itemInfo->duration)
        return;

    auto toDate = ServerTime::add(item->makeTime, item->itemInfo->duration);
    ItemDuration duration(ServerTime::to_time_t(toDate));

    if (duration.expired())
    {
        ItemDuration::sendDeleteNotice(user, item, bag, slot);
        return;
    }

    if (duration.days().count())
        return;

    ItemExpireNoticeOutgoing outgoing{};
    outgoing.type = item->type;
    outgoing.typeId = item->typeId;

    if (duration.hours().count())
    {
        outgoing.timeValue = duration.hours().count();

        if (bag == warehouse_bag)
            outgoing.noticeType = ItemExpireNoticeType::HoursLeftWarehouse;
        else
            outgoing.noticeType = ItemExpireNoticeType::HoursLeftInventory;
    }
    else
    {
        outgoing.timeValue = duration.minutes().count();

        if (bag == warehouse_bag)
            outgoing.noticeType = ItemExpireNoticeType::MinutesLeftWarehouse;
        else
            outgoing.noticeType = ItemExpireNoticeType::MinutesLeftInventory;
    }

    SConnection::Send(&user->connection, &outgoing, sizeof(ItemExpireNoticeOutgoing));
}
