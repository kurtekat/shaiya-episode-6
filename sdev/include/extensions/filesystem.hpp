#pragma once
#include <filesystem>

namespace ext {
namespace filesystem {
namespace path {

    template<class...Args>
    inline void combine(std::filesystem::path& base, const Args&...args)
    {
        for (const auto& path : std::initializer_list<std::filesystem::path>{ args... })
        {
            base /= path;
        }
    }

} // namespace path
} // namespace filesystem
} // namespace ext
