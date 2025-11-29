#include <chrono>
#include <shaiya/include/network/game/outgoing/1F00.h>
#include "CUser.h"
#include "NetworkHelper.h"
#include "RewardItem.h"
using namespace shaiya;

void RewardItemEvent::send(CUser* user)
{
    RewardItemEvent::sendItemList(user);
    RewardItemEvent::sendItemListIndex(user);
}

void RewardItemEvent::sendEnded(CUser* user)
{
    GameRewardItemEventEndedOutgoing outgoing{};
    NetworkHelper::Send(user, &outgoing, sizeof(GameRewardItemEventEndedOutgoing));
}

void RewardItemEvent::sendItemList(CUser* user)
{
    if (!g_rewardItemCount)
        return;

    GameRewardItemListOutgoing outgoing{};
    outgoing.itemCount = g_rewardItemCount;
    outgoing.itemList = g_rewardItemList;

    auto length = outgoing.baseLength + (outgoing.itemCount * sizeof(RewardItemUnit));
    NetworkHelper::Send(user, &outgoing, length);
}

void RewardItemEvent::sendItemListIndex(CUser* user)
{
    if (!g_rewardItemCount)
        return;

    if (auto it = g_rewardItemProgress.find(user->billingId); it != g_rewardItemProgress.end())
    {
        auto minutes = g_rewardItemList[it->second.index].minutes;
        auto ms = minutes * 60000 + 15000;
        auto now = std::chrono::system_clock::now();

        it->second.timeout = now + std::chrono::milliseconds(ms);
        it->second.completed = false;

        GameRewardItemListIndexOutgoing outgoing{};
        outgoing.index = it->second.index;
        NetworkHelper::Send(user, &outgoing, sizeof(GameRewardItemListIndexOutgoing));
    }
    else
    {
        auto minutes = g_rewardItemList[0].minutes;
        auto ms = minutes * 60000 + 15000;
        auto now = std::chrono::system_clock::now();

        RewardItemEventProgress progress{};
        progress.timeout = now + std::chrono::milliseconds(ms);
        g_rewardItemProgress.insert({ user->billingId, progress });

        GameRewardItemListIndexOutgoing outgoing{};
        NetworkHelper::Send(user, &outgoing, sizeof(GameRewardItemListIndexOutgoing));
    }
}
