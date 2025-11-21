#include <chrono>
#include <map>
#include <shaiya/include/network/game/outgoing/1F00.h>
#include "CUser.h"
#include "NetworkHelper.h"
#include "RewardItem.h"
using namespace shaiya;

void RewardItemEvent::sendItemList(CUser* user)
{
    if (!g_rewardItemCount)
        return;

    GameRewardItemListOutgoing outgoing{};
    outgoing.itemCount = g_rewardItemCount;
    outgoing.itemList = g_rewardItemList;
    
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
        auto minutes = std::chrono::minutes(g_rewardItemList[0].minutes);
        auto now = std::chrono::system_clock::now();

        RewardItemEventProgress progress{};
        progress.itemGetWaitTime = now + minutes;
        g_rewardItemEventProgress.insert({ user->billingId, progress });

        GameRewardItemEventProgressOutgoing outgoing{};
        NetworkHelper::Send(user, &outgoing, sizeof(GameRewardItemEventProgressOutgoing));
    }
}
