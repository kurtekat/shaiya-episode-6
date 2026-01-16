#pragma once
#include <filesystem>

namespace shaiya
{
    class Configuration final
    {
    public:

        static void Init();
        static void LoadBattlefieldMoveData();
        static void LoadChaoticSquareData();
        static void LoadItemSetData();
        static void LoadOnlineTimePrizeData();

    private:

        inline static std::filesystem::path m_root{};
    };
}
