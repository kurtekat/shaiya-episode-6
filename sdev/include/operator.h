#pragma once
#include <concepts>
#include <utility>
#include "extensions/concepts.hpp"

template<ext::scoped_enum L, std::integral R>
inline bool operator==(L lhs, R rhs)
{
    return std::to_underlying(lhs) == rhs;
}

template<std::integral L, ext::scoped_enum R>
inline bool operator==(L lhs, R rhs)
{
    return lhs == std::to_underlying(rhs);
}

template<ext::scoped_enum L, std::integral R>
inline bool operator!=(L lhs, R rhs)
{
    return std::to_underlying(lhs) != rhs;
}

template<std::integral L, ext::scoped_enum R>
inline bool operator!=(L lhs, R rhs)
{
    return lhs != std::to_underlying(rhs);
}
