#include <chrono>
#include <ranges>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/CWorld.h"
#include "include/shaiya/include/ItemDuration.h"
#include "include/shaiya/include/ItemInfo.h"
#include "include/shaiya/include/ServerTime.h"
using namespace shaiya;

namespace world_thread
{
    inline std::chrono::local_time<std::chrono::system_clock::duration> check_item_duration_time_point;

    void check_item_duration()
    {
        using namespace std::chrono;

        auto now = current_zone()->to_local(system_clock::now());
        if (now < check_item_duration_time_point)
            return;

        check_item_duration_time_point = now + 60s;

        for (const auto& charId : g_users)
        {
            auto user = CWorld::FindUser(charId);
            if (!user)
                continue;

            if (!user->zone)
                continue;

            if (user->where != UserWhere::ZoneEnter)
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
                        ItemDuration::sendDeleteNotice(user, item, bag, slot);
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
                    ItemDuration::sendDeleteNotice(user, item, warehouse_bag, slot);
            }
        }
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

        call world_thread::check_item_duration

        popad
     
        jmp u0x404076
    }
}

void hook::world_thread()
{
    // CWorldThread::Update
    util::detour((void*)0x404071, naked_0x404071, 5);
}
