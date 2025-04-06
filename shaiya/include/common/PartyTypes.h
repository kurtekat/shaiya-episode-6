#pragma once
#include <cstdint>

namespace shaiya
{
    enum struct DivType : int32_t
    {
        Group = 1,
        Random,
        Unknown,
        Master
    };

    enum struct PartyType : uint8_t
    {
        None,
        User,
        Boss
    };

    enum struct UnionType : int32_t
    {
        Default = -1,
        Boss,
        SubBoss,
        User
    };
}
