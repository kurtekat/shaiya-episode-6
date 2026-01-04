#pragma once
#include <type_traits>

namespace ext {

    template<class T>
    concept scoped_enum = std::is_scoped_enum_v<T>;

} // namespace ext
