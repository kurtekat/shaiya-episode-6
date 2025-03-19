#pragma once
#include <array>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// thanks, Cups ^^
#define CONCAT(x, y) x ## y
#define EXPAND(x, y) CONCAT(x, y)
#define PAD(size) char EXPAND(pad, __LINE__)[size]

namespace shaiya
{
    constexpr uint8_t max_equipment_slot = 24;
    constexpr uint8_t max_inventory_slot = 24;
    constexpr uint8_t max_warehouse_slot = 240;
    constexpr uint8_t min_warehouse_slot = 120;

    template<class T, size_t N>
    using Array = std::array<T, N>;

    template<size_t N>
    using CharArray = std::array<char, N>;
}
