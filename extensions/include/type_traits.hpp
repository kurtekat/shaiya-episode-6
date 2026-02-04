#pragma once
#include <type_traits>

namespace ext {

    template<class T>
    constexpr bool is_scoped_enum_v = std::conjunction_v<std::is_enum<T>, std::negation<std::is_convertible<T, int>>>;

    template<class T>
    struct is_scoped_enum : std::bool_constant<is_scoped_enum_v<T>> {};

} // namespace ext
