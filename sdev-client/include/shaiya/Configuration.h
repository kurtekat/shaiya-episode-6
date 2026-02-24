#pragma once
#include <filesystem>

namespace shaiya
{
    class Configuration final
    {
    public:

        static void Init();
        static void LoadBattlefieldMoveData();

    private:

        inline static std::filesystem::path m_root{};
    };
}
