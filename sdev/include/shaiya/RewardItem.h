#pragma once
#include <array>
#include <chrono>
#include <cstdint>
#include <map>

namespace shaiya
{
    struct CUser;
    struct RewardItemUnit;

    #pragma pack(push, 1)
    struct RewardItemEventProgress
    {
        uint32_t itemListIndex;
        std::chrono::system_clock::time_point itemGetWaitTime;
    };
    #pragma pack(pop)

    class RewardItemEvent
    {
    public:

        static void sendItemList(CUser* user);
    };

    inline uint32_t g_rewardItemCount{};
    inline std::array<RewardItemUnit, 20> g_rewardItemList{};
    inline std::map<uint32_t/*UserUID*/, RewardItemEventProgress> g_rewardItemEventProgress{};
}
