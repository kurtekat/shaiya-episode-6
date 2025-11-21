#pragma once
#include <array>
#include <cstdint>
#include <map>
#include <set>
#include <vector>

namespace shaiya
{
    struct CItem;
    struct CUser;

    struct ItemSetSynergy
    {
        std::array<int32_t, 12> effects;
    };

    struct ItemSet
    {
        using ItemId = uint32_t;

        int32_t id;
        std::array<ItemId, 13> items;
        std::array<ItemSetSynergy, 13> synergies;
    };

    #pragma pack(push, 1)
    class Synergy
    {
        using ItemId = uint32_t;

    public:

        static void equipmentAdd(CUser* user);
        static void equipmentRemove(CUser* user, int slot);
        static void removeSynergies(CUser* user);

    private:

        static void applySynergies(CUser* user, const std::vector<ItemSetSynergy>& synergies);
        static void getWornEquipment(CUser* user, std::set<ItemId>& equipment);
        static void getWornSynergies(const std::set<ItemId>& equipment, std::vector<ItemSetSynergy>& synergies);
    };
    #pragma pack(pop)

    inline std::vector<ItemSet> g_itemSets{};
    inline std::map<uint32_t/*CharID*/, std::vector<ItemSetSynergy>> g_itemSetSynergies{};
}
