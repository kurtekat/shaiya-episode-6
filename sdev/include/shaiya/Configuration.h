#pragma once
#include <cstdint>
#include <filesystem>

namespace shaiya
{
    struct ConfigurationConstants
    {
        static constexpr int MinItemId = 1 * 1000 + 1;
        static constexpr int MaxItemId = UINT8_MAX * 1000 + UINT8_MAX;
    };

    class Configuration final : public ConfigurationConstants
    {
    public:

        static void Init();
        static void LoadItemRemake4();
        static void LoadItemRemake5();
        static void LoadItemSetData();
        static void LoadItemSynthesis();
        static void LoadRewardItemEvent();

    private:

        inline static std::filesystem::path m_root{};
    };
}
