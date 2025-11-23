#pragma once
#include <cstdint>

namespace shaiya
{
    enum struct Bag : uint8_t
    {
        Warehouse = 100,
        Bank = 200,
        Unknown = 250,
        GuildWarehouse = 255,
        Skill = 100,
        BasicAction = 101
    };

    inline bool operator==(Bag lhs, int rhs)
    {
        return static_cast<int>(lhs) == rhs;
    }

    inline bool operator==(int lhs, Bag rhs)
    {
        return lhs == static_cast<int>(rhs);
    }

    inline bool operator!=(Bag lhs, int rhs)
    {
        return static_cast<int>(lhs) != rhs;
    }

    inline bool operator!=(int lhs, Bag rhs)
    {
        return lhs != static_cast<int>(rhs);
    }
}
