#include <chrono>
#include <filesystem>
#include <ranges>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <util/ini/ini.h>
#include <shaiya/include/network/game/outgoing/1F00.h>
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/CWorld.h"
#include "include/shaiya/include/NetworkHelper.h"
#include "include/shaiya/include/RewardItem.h"
using namespace shaiya;

void RewardItemEvent::init()
{
    try
    {
        std::wstring buffer(INT16_MAX, 0);
        if (!GetModuleFileNameW(nullptr, buffer.data(), INT16_MAX))
            return;

        std::filesystem::path path(buffer);
        path.remove_filename();
        path.append("Data");
        path.append("RewardItem.ini");

        if (!std::filesystem::exists(path))
            return;

        for (const auto& section : util::ini::get_sections(path))
        {
            auto pairs = util::ini::get_pairs(section.c_str(), path);
            if (pairs.size() != 4)
                continue;

            auto delay = std::stoi(pairs[0].second);
            if (delay <= 0)
                continue;

            RewardItem item{};
            item.delay = std::chrono::minutes(delay);
            item.type = std::stoi(pairs[1].second);
            item.typeId = std::stoi(pairs[2].second);
            item.count = std::stoi(pairs[3].second);
            g_rewardItems.push_back(item);

            if (g_rewardItems.size() == maxItemCount)
                break;
        }
    }
    catch (...)
    {
        g_rewardItems.clear();
    }
}

void RewardItemEvent::sendItemList(CUser* user)
{
    if (g_rewardItems.empty())
        return;

    GameRewardItemListOutgoing outgoing{};
    outgoing.itemCount = static_cast<uint32_t>(g_rewardItems.size());

    for (auto&& [dest, item] : std::views::zip(
        outgoing.itemList,
        std::as_const(g_rewardItems)))
    {
        dest.minutes = item.delay.count();
        dest.type = item.type;
        dest.typeId = item.typeId;
        dest.count = item.count;
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
