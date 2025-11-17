#pragma once
#include <chrono>
#include <map>
#include <vector>
#include <shaiya/include/common.h>

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

        static constexpr uint32_t maxItemCount = 20;
    };

    inline std::vector<RewardItem> g_rewardItems;
    inline std::map<uint32_t, RewardItemEventProgress> g_rewardItemEventProgress;
}
