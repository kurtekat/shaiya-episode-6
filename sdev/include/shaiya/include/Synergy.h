#pragma once
#include <array>
#include <map>
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
        static void applySynergies(CUser* user, CItem* item, bool removeFlag);
        static void removeSynergies(CUser* user);

    private:

        static void getWornSynergies(CUser* user, CItem* item, std::vector<SynergyEffect>& effects, bool removeFlag);
    };
    #pragma pack(pop)

    inline std::vector<Synergy> g_synergies;
    inline std::map<CharId, std::vector<SynergyEffect>> g_appliedSynergies;
}
