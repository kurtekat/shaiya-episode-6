#pragma once
#include <filesystem>

namespace ext {
    namespace filesystem {

        template<class...Args>
        inline void combine(std::filesystem::path& base, const Args&...args)
        {
            for (const auto& path : std::initializer_list<std::filesystem::path>{ args... })
            {
                base /= path;
            }
        }

    } // namespace filesystem
} // namespace ext
