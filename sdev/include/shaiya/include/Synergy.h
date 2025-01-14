#pragma once
#include <array>
#include <map>
#include <set>
#include <vector>
#include <shaiya/include/common/ItemTypes.h>
#include <shaiya/include/common/UserTypes.h>

namespace shaiya
{
    struct CItem;
    struct CUser;

    using SynergyEffect = std::array<int, 12>;

    #pragma pack(push, 1)
    struct Synergy
    {
        int id;
        std::array<SynergyEffect, 13> effects;
        std::array<ItemId, 13> set;

        static void init();
        static void equipmentAdd(CUser* user);
        static void equipmentRemove(CUser* user, int slot);
        static void removeSynergies(CUser* user);

    private:

        static void applySynergies(CUser* user, const std::vector<SynergyEffect>& effects);
        static void getWornEquipment(CUser* user, std::set<ItemId>& equipment);
        static void getWornSynergies(const std::set<ItemId>& equipment, std::vector<SynergyEffect>& effects);
    };
    #pragma pack(pop)

    inline std::vector<Synergy> g_synergies;
    inline std::map<CharId, std::vector<SynergyEffect>> g_appliedSynergies;
}
