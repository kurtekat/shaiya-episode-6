#pragma once
#include <array>
#include <cstdint>
#include <shaiya/include/network/game/RewardItemUnit.h>

namespace shaiya
{
    using BillingId = uint32_t;

    struct CUser;

    class RewardItemEvent
    {
    public:

        static void send(CUser* user);
        static void sendEnded(CUser* user);
        static void sendItemList(CUser* user);
        static void sendItemListIndex(CUser* user);
    };

    inline uint32_t g_rewardItemCount{ 0 };
    inline std::array<RewardItemUnit, 20> g_rewardItemList{};
}
