#pragma once
#include <array>
#include <map>
#include <vector>
#include <shaiya/include/common.h>

namespace shaiya
{
    struct CItem;
    struct CUser;

    class Synergy
    {
    public:

        using Effect = std::array<int, 12>;

        int id;
        std::array<Effect, 13> effects{};
        std::array<ItemId, 13> set{};

        static void init();
        static void applySynergies(CUser* user, CItem* item, bool removeFlag);
        static void removeSynergies(CUser* user);

        Synergy()
            : id(0)
        {
        }

    private:

        static void getWornSynergies(CUser* user, CItem* item, std::vector<Synergy::Effect>& effects, bool removeFlag);
    };

    inline std::vector<Synergy> g_synergies;
    inline std::map<CharId, std::vector<Synergy::Effect>> g_appliedSynergies;
}
