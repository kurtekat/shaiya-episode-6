#pragma once
#include <filesystem>
#include <map>
#include <string>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace shaiya
{
    class Ini
    {
    public:

        explicit Ini(const std::filesystem::path& path)
            : m_path(path)
        {
        }

        std::wstring GetValueOrDefault(const std::wstring& key, const std::wstring& defaultValue) const;
        int GetValueOrDefault(const std::wstring& key, int defaultValue) const;
        void Read();

    private:

        struct key_compare
        {
            bool operator()(const std::wstring& lhs, const std::wstring& rhs) const
            {
                return CompareStringOrdinal(
                    lhs.data(), lhs.size(), rhs.data(), rhs.size(), true) == CSTR_LESS_THAN;
            }
        };

        std::map<std::wstring, std::wstring, key_compare> m_data;
        std::filesystem::path m_path;
        std::wstring GetString(const wchar_t* section, const wchar_t* key, const wchar_t* defaultValue) const;
    };
}
