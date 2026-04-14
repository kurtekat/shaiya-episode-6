#pragma once
#include <array>
#include <cstdint>
#include <map>
#include <set>
#include <vector>

namespace shaiya
{
    using CharId = uint32_t;

    struct CUser;

    struct ItemSetSynergy
    {
        std::array<int32_t, 15> effects;
    };

    struct ItemSet
    {
        int32_t id; // ItemInfo.Drop
        std::array<ItemSetSynergy, 13> synergies;
    };

    struct Synergy
    {
        static void subSynergies(CUser* user, const std::vector<ItemSetSynergy>& synergies);
        static void addSynergies(CUser* user, const std::vector<ItemSetSynergy>& synergies);
        static void getSynergies(CUser* user, std::vector<ItemSetSynergy>& synergies);
    };

    inline std::vector<ItemSet> g_itemSets{};
    inline std::map<CharId, std::vector<ItemSetSynergy>> g_itemSetSynergies{};
}
