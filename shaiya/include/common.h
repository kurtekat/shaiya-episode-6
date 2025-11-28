#pragma once
#include <array>
#include <cstddef>
#include <cstdint>

// thanks, Cups ^^
#define CONCAT(x, y) x ## y
#define EXPAND(x, y) CONCAT(x, y)
#define PAD(size) char EXPAND(pad, __LINE__)[size]

namespace shaiya
{
    using bool32_t = uint32_t;
    using tick32_t = uint32_t;
    using time32_t = uint32_t;

    template<class T, size_t N>
    using Array = std::array<T, N>;

    template<size_t N>
    using String = std::array<char, N>;
}
