#include <chrono>
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

    if (auto it = g_rewardItemEvents.find(user->billingId); it != g_rewardItemEvents.end())
    {
        auto minutes = std::chrono::minutes(g_rewardItemList[it->second.index].minutes);
        auto now = std::chrono::system_clock::now();
        it->second.progress.timeout = now + minutes;
        it->second.progress.completed = false;

        GameRewardItemEventIndexOutgoing outgoing{};
        outgoing.index = it->second.index;
        NetworkHelper::Send(user, &outgoing, sizeof(GameRewardItemEventIndexOutgoing));
    }
    else
    {
        auto minutes = std::chrono::minutes(g_rewardItemList[0].minutes);
        auto now = std::chrono::system_clock::now();

        RewardItemEvent event{};
        event.progress.timeout = now + minutes;
        g_rewardItemEvents.insert({ user->billingId, event });

        GameRewardItemEventIndexOutgoing outgoing{};
        NetworkHelper::Send(user, &outgoing, sizeof(GameRewardItemEventIndexOutgoing));
    }
}
