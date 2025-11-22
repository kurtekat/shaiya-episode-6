#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    inline constexpr int ItemEnchant_MAX = 20;

    #pragma pack(push, 1)
    struct LapisionEnchantStep16
    {
        uint16_t weapon;
        uint16_t defense;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct LapisionEnchantStep32
    {
        uint32_t weapon;
        uint32_t defense;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct LapisianEnchantSuccessRate
    {
        Array<LapisionEnchantStep32, 21> step;
    };
    #pragma pack(pop)

    static_assert(sizeof(LapisianEnchantSuccessRate) == 0xA8);

    #pragma pack(push, 1)
    struct LapisianEnchantAddValue
    {
        Array<LapisionEnchantStep16, 21> step;
    };
    #pragma pack(pop)

    static_assert(sizeof(LapisianEnchantAddValue) == 0x54);

    static auto g_LapisianEnchantSuccessRate = (LapisianEnchantSuccessRate*)0x581C88;
    static auto g_LapisianEnchantAddValue = (LapisianEnchantAddValue*)0x581D30;
}
