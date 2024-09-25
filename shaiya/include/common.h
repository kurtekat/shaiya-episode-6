#pragma once
#define SHAIYA_EP6_4_PT

#include <array>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// thanks, Cups ^^
#define CONCAT(x, y) x ## y
#define EXPAND(x, y) CONCAT(x, y)
#define PAD(size) char EXPAND(pad, __LINE__)[size]

namespace shaiya
{
    constexpr int max_equipment_slot = 24;
    constexpr int max_inventory_slot = 24;
    constexpr int max_warehouse_slot = 240;
    constexpr int min_warehouse_slot = 120;

    template<class T, size_t N>
    using Array = std::array<T, N>;

    template<size_t N>
    using CharArray = std::array<char, N>;

    using UserId = unsigned long;
    using CharId = unsigned long;
    using ItemId = uint32_t;

    enum struct Bag : uint8_t
    {
        Warehouse = 100,
        Bank = 200,
        Unknown = 250,
        GuildWarehouse = 255,
        Skill = 100,
        BasicAction = 101
    };
}
