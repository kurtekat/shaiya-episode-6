#include <chrono>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/CWorld.h"
#include "include/shaiya/include/ItemDuration.h"
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

            if (user->logoutTick)
                continue;

            ItemDuration::checkExpireInventory(user);
            ItemDuration::checkExpireWarehouse(user);
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
