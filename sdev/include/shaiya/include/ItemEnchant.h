#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    struct LapisianEnchantSuccessRate
    {
        std::array<std::array<uint32_t, 2>, 20> value;
    };

    struct LapisianEnchantAddValue
    {
        std::array<std::array<uint16_t, 2>, 20> value;
    };

    static auto g_LapisianEnchantSuccessRate = (LapisianEnchantSuccessRate*)0x581C88;
    static auto g_LapisianEnchantAddValue = (LapisianEnchantAddValue*)0x581D30;
}
