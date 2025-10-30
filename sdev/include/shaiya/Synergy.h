#pragma once
#include <map>
#include <set>
#include <vector>
#include <shaiya/include/common.h>

namespace shaiya
{
    struct CItem;
    struct CUser;

    #pragma pack(push, 1)
    struct Synergy
    {
        using ItemId = uint32_t;
        using StatusEffects = Array<int32_t, 12>;

        int32_t id;
        Array<StatusEffects, 13> effects;
        Array<ItemId, 13> set;

        static void init();
        static void equipmentAdd(CUser* user);
        static void equipmentRemove(CUser* user, int slot);
        static void removeSynergies(CUser* user);

    private:

        static void applySynergies(CUser* user, const std::vector<StatusEffects>& effects);
        static void getWornEquipment(CUser* user, std::set<ItemId>& equipment);
        static void getWornSynergies(const std::set<ItemId>& equipment, std::vector<StatusEffects>& effects);
    };
    #pragma pack(pop)

    inline std::vector<Synergy> g_synergies;
    inline std::map<uint32_t, std::vector<Synergy::StatusEffects>> g_appliedSynergies;
}
