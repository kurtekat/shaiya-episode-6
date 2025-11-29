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

    class RewardItemEvent
    {
    public:

        static void send(CUser* user);
        static void sendEnded(CUser* user);
        static void sendItemList(CUser* user);
        static void sendItemListIndex(CUser* user);
    };

    class RewardItemEventProgress
    {
    public:

        uint32_t index{ 0 };
        std::chrono::system_clock::time_point timeout;
        std::atomic<bool> completed;

        RewardItemEventProgress() = default;

        RewardItemEventProgress(RewardItemEventProgress& other)
        {
            *this = other;
        }

        RewardItemEventProgress& operator=(RewardItemEventProgress& other)
        {
            if (this != &other)
            {
                index = other.index;
                timeout = other.timeout;
                completed.store(other.completed.load());
            }

            return *this;
        }

        RewardItemEventProgress(RewardItemEventProgress&& other) noexcept
        {
            *this = std::move(other);
        }

        RewardItemEventProgress& operator=(RewardItemEventProgress&& other) noexcept
        {
            if (this != &other)
            {
                index = std::exchange(other.index, 0);
                timeout = std::move(other.timeout);
                completed.store(other.completed.load());
            }

            return *this;
        }
    };

    inline uint32_t g_rewardItemCount{ 0 };
    inline std::array<RewardItemUnit, 20> g_rewardItemList{};
    inline std::map<uint32_t/*UserUID*/, RewardItemEventProgress> g_rewardItemProgress{};
}
