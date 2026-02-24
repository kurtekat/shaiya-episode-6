#pragma once
#include <filesystem>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace shaiya
{
    class Ini
    {
    public:

        Ini() = default;

        static Ini Parse(const std::filesystem::path& path);
        static Ini Parse(std::wifstream& stream);
        static Ini Parse(const std::wstring& rawData);
        static Ini Parse(std::wstringstream& rawData);

        std::wstring GetValueOrDefault(const std::wstring& key, const std::wstring& defaultValue) const;
        int GetValueOrDefault(const std::wstring& key, int defaultValue) const;

    private:

        struct key_compare
        {
            bool operator()(const std::wstring& lhs, const std::wstring& rhs) const
            {
                return CompareStringOrdinal(
                    lhs.data(), lhs.size(), rhs.data(), rhs.size(), true) == CSTR_LESS_THAN;
            }
        };

        std::map<std::wstring, std::wstring, key_compare> data;
    };
}
