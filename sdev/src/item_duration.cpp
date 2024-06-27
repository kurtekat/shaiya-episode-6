#include <chrono>
#include <ranges>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common/SConnection.h>
#include <shaiya/include/network/dbAgent/incoming/0700.h>
#include <shaiya/include/network/game/outgoing/0200.h>
#include <shaiya/include/network/gameLog/incoming/0400.h>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CObjectMgr.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/CWorld.h"
#include "include/shaiya/include/Helpers.h"
#include "include/shaiya/include/ItemDuration.h"
#include "include/shaiya/include/ItemInfo.h"
#include "include/shaiya/include/ServerTime.h"
using namespace shaiya;

namespace item_duration
{
    inline std::chrono::system_clock::time_point g_world_thread_update_time_point{};

    void send_delete_notice(CUser* user, CItem* item, uint8_t bag, uint8_t slot)
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

    void send_expire_notice(CUser* user, CItem* item, uint8_t bag, uint8_t slot)
    {
        if (!item->itemInfo->duration)
            return;

        auto toDate = ServerTime::add(item->makeTime, item->itemInfo->duration);
        ItemDuration duration(ServerTime::to_time_t(toDate));

        if (duration.expired())
        {
            send_delete_notice(user, item, bag, slot);
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

    void send(CUser* user, CItem* item, uint8_t bag, uint8_t slot)
    {
        if (!item->itemInfo->duration)
            return;

        auto toDate = ServerTime::add(item->makeTime, item->itemInfo->duration);

        ItemDurationOutgoing outgoing(bag, slot, item->makeTime, toDate);
        SConnection::Send(&user->connection, &outgoing, sizeof(ItemDurationOutgoing));

        send_expire_notice(user, item, bag, slot);
    }

    void send_bag_and_bank(CUser* user)
    {
        for (const auto& [bag, items] : std::views::enumerate(
            std::as_const(user->inventory)))
        {
            for (const auto& [slot, item] : std::views::enumerate(
                std::as_const(items)))
            {
                if (!item)
                    continue;

                send(user, item, bag, slot);
            }
        }

        for (const auto& [slot, item] : std::views::enumerate(
            std::as_const(user->warehouse)))
        {
            if (!item)
                continue;

            send(user, item, warehouse_bag, slot);
        }
    }

    void send_bag_to_bank(CUser* user, Packet buffer)
    {
        auto slot = util::deserialize<uint8_t>(buffer, 37);
        if (slot >= user->warehouse.size())
            return;

        auto& item = user->warehouse[slot];
        if (!item)
            return;

        if (!item->itemInfo->duration)
            return;

        auto toDate = ServerTime::add(item->makeTime, item->itemInfo->duration);

        ItemDurationOutgoing outgoing(warehouse_bag, slot, item->makeTime, toDate);
        SConnection::Send(&user->connection, &outgoing, sizeof(ItemDurationOutgoing));
    }

    void send_item_create(CUser* user, CItem* item, Packet buffer)
    {
        if (!item->itemInfo->duration)
            return;

        auto bag = util::deserialize<uint8_t>(buffer, 2);
        auto slot = util::deserialize<uint8_t>(buffer, 3);
        auto toDate = ServerTime::add(item->makeTime, item->itemInfo->duration);

        ItemDurationOutgoing outgoing(bag, slot, item->makeTime, toDate);
        SConnection::Send(&user->connection, &outgoing, sizeof(ItemDurationOutgoing));
    }

    void world_thread_update()
    {
        auto now = std::chrono::system_clock::now();
        if (now < g_world_thread_update_time_point)
            return;

        g_world_thread_update_time_point = now + std::chrono::minutes(1);

        for (const auto& charId : g_users)
        {
            auto user = CWorld::FindUser(charId);
            if (!user)
            {
                std::erase(g_users, charId);
                continue;
            }

            if (!user->zone)
                continue;

            for (const auto& [bag, items] : std::views::enumerate(
                std::as_const(user->inventory)))
            {
                for (const auto& [slot, item] : std::views::enumerate(
                    std::as_const(items)))
                {
                    if (user->where != UserWhere::ZoneEnter)
                        break;

                    if (!item)
                        continue;

                    if (!item->itemInfo->duration)
                        continue;

                    auto toDate = ServerTime::add(item->makeTime, item->itemInfo->duration);
                    ItemDuration duration(ServerTime::to_time_t(toDate));

                    if (duration.expired())
                        send_delete_notice(user, item, bag, slot);
                }
            }

            for (const auto& [slot, item] : std::views::enumerate(
                std::as_const(user->warehouse)))
            {
                if (user->where != UserWhere::ZoneEnter)
                    break;

                if (!user->doubleWarehouse && slot >= min_warehouse_slot)
                    break;

                if (!item)
                    continue;

                if (!item->itemInfo->duration)
                    continue;

                auto toDate = ServerTime::add(item->makeTime, item->itemInfo->duration);
                ItemDuration duration(ServerTime::to_time_t(toDate));

                if (duration.expired())
                    send_delete_notice(user, item, warehouse_bag, slot);
            }
        }
    }
}

// CUser::EnterZone
unsigned u0x455E70 = 0x455E70;
unsigned u0x41C922 = 0x41C922;
void __declspec(naked) naked_0x41C91D()
{
    __asm
    {
        // original
        call u0x455E70

        pushad

        push edi // user
        call item_duration::send_bag_and_bank
        add esp,0x4

        popad
     
        jmp u0x41C922
    }
}

unsigned u0x4ED0E0 = 0x4ED0E0;
unsigned u0x469934 = 0x469934;
void __declspec(naked) naked_0x46992F()
{
    __asm
    {
        // original
        call u0x4ED0E0

        pushad

        lea edx,[esp+0x40]

        push edx // packet
        push edi // user
        call item_duration::send_bag_to_bank
        add esp,0x8

        popad
     
        jmp u0x469934
    }
}

unsigned u0x46C22F = 0x46C22F;
void __declspec(naked) naked_0x46C22A()
{
    __asm
    {
        // original
        call u0x4ED0E0

        pushad

        lea edx,[esp+0xB4]
        mov ecx,[esp+0x38]

        push edx // packet
        push ebp // item
        push ecx // user
        call item_duration::send_item_create
        add esp,0xC

        popad
     
        jmp u0x46C22F
    }
}

// CWorldThread::UpdateKillCount
unsigned u0x4042A0 = 0x4042A0;
unsigned u0x404076 = 0x404076;
void __declspec(naked) naked_0x404071()
{
    __asm
    {
        // original
        call u0x4042A0

        pushad

        call item_duration::world_thread_update

        popad
     
        jmp u0x404076
    }
}

void hook::item_duration()
{
    // CZone::EnterUser
    util::detour((void*)0x41C91D, naked_0x41C91D, 5);
    // CUser::ItemBagToBank
    util::detour((void*)0x46992F, naked_0x46992F, 5);
    // CUser::ItemCreate
    util::detour((void*)0x46C22A, naked_0x46C22A, 5);
    // CWorldThread::Update
    util::detour((void*)0x404071, naked_0x404071, 5);
}
