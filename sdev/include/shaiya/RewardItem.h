#pragma once
#include <chrono>
#include <cstdint>
#include <map>
#include <vector>

namespace shaiya
{
    struct CUser;

    #pragma pack(push, 1)
    struct RewardItem
    {
        std::chrono::minutes delay;
        uint8_t type;
        uint8_t typeId;
        uint8_t count;
    };
    #pragma pack(pop)

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

        /// <summary>
        /// The max reward items read by the client.
        /// </summary>
        static constexpr uint32_t MaxItemCount = 20;
    };

    inline std::vector<RewardItem> g_rewardItems{};
    inline std::map<uint32_t/*UserUID*/, RewardItemEventProgress> g_rewardItemEventProgress{};
}
