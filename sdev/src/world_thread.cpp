#include <chrono>
#include <util/util.h>
#include <shaiya/include/network/game/outgoing/1F00.h>
#include "include/main.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/CWorld.h"
#include "include/shaiya/ItemInfo.h"
#include "include/shaiya/NetworkHelper.h"
#include "include/shaiya/RewardItem.h"
using namespace shaiya;

namespace world_thread
{
    inline std::chrono::system_clock::time_point next_update_reward_item_event_progress;

    void update_reward_item_event_progress()
    {
        using namespace std::chrono;

        auto now = std::chrono::system_clock::now();
        if (now < next_update_reward_item_event_progress)
            return;

        next_update_reward_item_event_progress = now + 3000ms;

        for (const auto& [billingId, progress] : g_rewardItemEventProgress)
        {
            auto now = std::chrono::system_clock::now();
            if (now < progress.itemGetWaitTime)
                continue;

            auto user = CWorld::FindUserBill(billingId);
            if (!user)
                continue;

            GameRewardItemGetOutgoing outgoing{};
            NetworkHelper::Send(user, &outgoing, sizeof(GameRewardItemGetOutgoing));
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

        call world_thread::update_reward_item_event_progress

        popad
     
        jmp u0x404076
    }
}

void hook::world_thread()
{
    // CWorldThread::Update
    util::detour((void*)0x404071, naked_0x404071, 5);
}
