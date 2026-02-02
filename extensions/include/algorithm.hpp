#pragma once
#include <algorithm>

namespace ext {

    template<class Container, class Value>
    inline bool contains(Container cont, Value val)
    {
        auto first = std::cbegin(cont);
        auto last = std::cend(cont);
        return std::find(first, last, val) != last;
    }

} // namespace ext
