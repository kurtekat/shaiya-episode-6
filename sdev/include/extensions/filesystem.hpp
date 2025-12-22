#pragma once
#include <filesystem>

namespace ext
{
    namespace filesystem
    {
        struct path
        {
            template<class...Args>
            static void combine(std::filesystem::path& base, const Args&...args)
            {
                for (const auto& path : std::initializer_list<std::filesystem::path>{ args... })
                {
                    base /= path;
                }
            }
        };

    } // namespace filesystem
} // namespace ext
