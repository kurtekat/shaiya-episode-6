#pragma once
#include <array>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <map>

namespace shaiya
{
    struct CUser;
    struct RewardItemUnit;

    struct RewardItemProgress
    {
        std::chrono::system_clock::time_point timeout;
        std::atomic<bool> completed;
    };

    class RewardItemEvent
    {
    public:

        uint32_t index{ 0 };
        RewardItemProgress progress{};

        RewardItemEvent() = default;

        RewardItemEvent(RewardItemEvent& other)
        {
            *this = other;
        }

        RewardItemEvent& operator=(RewardItemEvent& other)
        {
            if (this != &other)
            {
                index = other.index;
                progress.timeout = other.progress.timeout;
                progress.completed.store(other.progress.completed.load());
            }

            return *this;
        }

        RewardItemEvent(RewardItemEvent&& other) noexcept
        {
            *this = std::move(other);
        }

        RewardItemEvent& operator=(RewardItemEvent&& other) noexcept
        {
            if (this != &other)
            {
                index = std::exchange(other.index, 0);
                progress.timeout = std::move(other.progress.timeout);
                progress.completed.store(other.progress.completed.load());
            }

            return *this;
        }

        static void sendItemList(CUser* user);
    };

    inline uint32_t g_rewardItemCount{ 0 };
    inline std::array<RewardItemUnit, 20> g_rewardItemList{};
    inline std::map<uint32_t/*UserUID*/, RewardItemEvent> g_rewardItemEvents{};
}
