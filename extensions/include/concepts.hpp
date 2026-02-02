#pragma once
#include "type_traits.hpp"

namespace ext {

    template<class T>
    concept scoped_enum = ext::is_scoped_enum_v<T>;

} // namespace ext
