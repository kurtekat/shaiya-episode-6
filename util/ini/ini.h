#pragma once
#include <filesystem>
#include <string>
#include <vector>

namespace util
{
    namespace ini
    {
        int delete_key(const wchar_t* section, const wchar_t* key, const std::filesystem::path& path);
        int delete_section(const wchar_t* section, const std::filesystem::path& path);
        std::vector<std::wstring> get_keys(const wchar_t* section, const std::filesystem::path& path);
        std::vector<std::pair<std::wstring, std::wstring>> get_pairs(const wchar_t* section, const std::filesystem::path& path);
        std::vector<std::wstring> get_sections(const std::filesystem::path& path);
        unsigned get_value(const wchar_t* section, const wchar_t* key, int defaultValue, const std::filesystem::path& path);
        std::wstring get_value(const wchar_t* section, const wchar_t* key, const wchar_t* defaultValue, const std::filesystem::path& path);
        int set_value(const wchar_t* section, const wchar_t* key, const wchar_t* value, const std::filesystem::path& path);
    }
}
