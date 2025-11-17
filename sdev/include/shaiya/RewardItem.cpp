#include <chrono>
#include <ranges>
#include <vector>
#include <shaiya/include/network/game/outgoing/1F00.h>
#include "CUser.h"
#include "CWorld.h"
#include "NetworkHelper.h"
#include "RewardItem.h"
using namespace shaiya;

void RewardItemEvent::sendItemList(CUser* user)
{
    if (g_rewardItems.empty())
        return;

    GameRewardItemListOutgoing outgoing{};
    outgoing.itemCount = static_cast<uint32_t>(g_rewardItems.size());

    for (auto&& [unit, item] : std::views::zip(
        outgoing.itemList,
        std::as_const(g_rewardItems)))
    {
        unit.minutes = item.delay.count();
        unit.type = item.type;
        unit.typeId = item.typeId;
        unit.count = item.count;
    }
    
    auto length = outgoing.baseLength + (outgoing.itemCount * sizeof(RewardItemUnit));
    NetworkHelper::Send(user, &outgoing, length);

    if (auto it = g_rewardItemEventProgress.find(user->billingId); it != g_rewardItemEventProgress.end())
    {
        GameRewardItemEventProgressOutgoing outgoing{};
        outgoing.itemListIndex = it->second.itemListIndex;
        NetworkHelper::Send(user, &outgoing, sizeof(GameRewardItemEventProgressOutgoing));
    }
    else
    {
        auto now = std::chrono::system_clock::now();

        RewardItemEventProgress progress{};
        progress.itemListIndex = 0;
        progress.itemGetWaitTime = now + g_rewardItems[0].delay;
        g_rewardItemEventProgress.insert({ user->billingId, progress });

        GameRewardItemEventProgressOutgoing outgoing{};
        NetworkHelper::Send(user, &outgoing, sizeof(GameRewardItemEventProgressOutgoing));
    }
}
