#pragma once
#include <concepts>
#include "include/extensions/concepts.hpp"

namespace shaiya
{
    template<ext::scoped_enum L, std::integral R>
    inline bool operator==(L lhs, R rhs)
    {
        return static_cast<R>(lhs) == rhs;
    }

    template<std::integral L, ext::scoped_enum R>
    inline bool operator==(L lhs, R rhs)
    {
        return lhs == static_cast<L>(rhs);
    }

    template<ext::scoped_enum L, std::integral R>
    inline bool operator!=(L lhs, R rhs)
    {
        return static_cast<R>(lhs) != rhs;
    }

    template<std::integral L, ext::scoped_enum R>
    inline bool operator!=(L lhs, R rhs)
    {
        return lhs != static_cast<L>(rhs);
    }
}
