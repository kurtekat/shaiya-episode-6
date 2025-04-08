#pragma once
#include <array>
#include <cstdint>

// thanks, Cups ^^
#define CONCAT(x, y) x ## y
#define EXPAND(x, y) CONCAT(x, y)
#define PAD(size) char EXPAND(pad, __LINE__)[size]

namespace shaiya
{
    constexpr int max_equipment_slot = 24;
    constexpr int max_inventory_slot = 24;

    using bool32_t = uint32_t;
    using tick32_t = uint32_t;
    using time32_t = uint32_t;

    using uint = unsigned int;

    template<class T, size_t N>
    using Array = std::array<T, N>;

    template<size_t N>
    using String = std::array<char, N>;
}
