#pragma once
#include <filesystem>

namespace shaiya
{
    class PathHelper
    {
    public:

        template<class T>
        static std::filesystem::path& combine(
            std::filesystem::path& path1, const T& path2)
        {
            return path1 /= path2;
        }

        template<class T1, class T2>
        static std::filesystem::path& combine(
            std::filesystem::path& path1, const T1& path2, const T2& path3)
        {
            return (path1 /= path2) /= path3;
        }

        template<class T1, class T2, class T3>
        static std::filesystem::path& combine(
            std::filesystem::path& path1, const T1& path2, const T2& path3, const T3& path4)
        {
            return ((path1 /= path2) /= path3) /= path4;
        }
    };
}
