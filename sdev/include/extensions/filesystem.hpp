#pragma once
#include <filesystem>

namespace ext {
    namespace filesystem {

        template<class...Args>
        inline std::filesystem::path& combine(std::filesystem::path& base, const Args&...args)
        {
            for (const auto& path : std::initializer_list<std::filesystem::path>{ args... })
            {
                base /= path;
            }

            return base;
        }

    } // namespace filesystem
} // namespace ext
