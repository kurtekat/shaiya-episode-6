#pragma once
#include <filesystem>
#include <limits>
#include <map>
#include <string>

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

        std::map<std::wstring, std::wstring> m_data;
        std::filesystem::path m_path;
        std::wstring GetString(const wchar_t* section, const wchar_t* key, const wchar_t* defaultValue) const;
    };
}
