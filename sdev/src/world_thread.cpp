#include <chrono>
#include <util/util.h>
#include <shaiya/include/network/game/outgoing/1F00.h>
#include "include/main.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/CWorld.h"
#include "include/shaiya/ItemInfo.h"
#include "include/shaiya/RewardItem.h"
#include "include/shaiya/SConnection.h"
using namespace shaiya;

inline std::chrono::system_clock::time_point next_update_reward_item_event;

void hook_0x404071()
{
    using namespace std::chrono_literals;

    auto now = std::chrono::system_clock::now();
    if (now < next_update_reward_item_event)
        return;

    next_update_reward_item_event = now + 3000ms;

    for (auto&& [billingId, progress] : g_rewardItemProgress)
    {
        if (progress.completed)
            continue;

        auto now = std::chrono::system_clock::now();
        if (now < progress.timeout)
            continue;

        progress.completed = true;

        auto user = CWorld::FindUserBill(billingId);
        if (!user)
            continue;

        GameRewardItemGetOutgoing outgoing{};
        SConnection::Send(user, &outgoing, sizeof(GameRewardItemGetOutgoing));
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

        call hook_0x404071

        popad
     
        jmp u0x404076
    }
}

void hook::world_thread()
{
    // CWorldThread::Update
    util::detour((void*)0x404071, naked_0x404071, 5);
}
