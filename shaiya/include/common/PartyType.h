#pragma once
#include <cstdint>

namespace shaiya
{
    enum struct PartyType : uint8_t
    {
        None,
        Member,
        Leader
    };

    enum struct RaidPartyType : uint32_t
    {
        Leader,
        SubLeader,
        Member,
        Default = UINT32_MAX
    };
}
