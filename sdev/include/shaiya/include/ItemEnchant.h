#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct LapisionEnchantStep16
    {
        UINT16 weapon;
        UINT16 defense;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct LapisionEnchantStep32
    {
        UINT32 weapon;
        UINT32 defense;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct LapisianEnchantSuccessRate
    {
        Array<LapisionEnchantStep32, 21> step;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct LapisianEnchantAddValue
    {
        Array<LapisionEnchantStep16, 21> step;
    };
    #pragma pack(pop)

    static auto g_LapisianEnchantSuccessRate = (LapisianEnchantSuccessRate*)0x581C88;
    static auto g_LapisianEnchantAddValue = (LapisianEnchantAddValue*)0x581D30;
}
