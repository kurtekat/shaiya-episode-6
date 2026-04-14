#pragma once
#include <atomic>
#include <chrono>
#include <cstdint>
#include <map>

namespace shaiya
{
    using BillingId = uint32_t;

    struct RewardItemProgress
    {
        uint32_t index{ 0 };
        std::chrono::system_clock::time_point timeout;
        std::atomic<bool> completed;

        RewardItemProgress() = default;
        RewardItemProgress(const RewardItemProgress& other);
        RewardItemProgress(RewardItemProgress&& other) noexcept;

        RewardItemProgress& operator=(const RewardItemProgress& other);
        RewardItemProgress& operator=(RewardItemProgress&& other) noexcept;
    };

    inline std::map<BillingId, RewardItemProgress> g_rewardItemProgress{};
}

