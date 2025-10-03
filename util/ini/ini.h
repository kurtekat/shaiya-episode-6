#pragma once
#include <filesystem>
#include <string>
#include <vector>

namespace util
{
    namespace ini
    {
        /// <summary>
        /// Deletes the key-value pair associated with the section name. The section name is case-insensitive. 
        /// If the function succeeds, the return value is nonzero.
        /// </summary>
        int delete_key(const wchar_t* section, const wchar_t* key, const std::filesystem::path& path);

        /// <summary>
        /// Deletes the section name and the associated key-value pairs. The section name is case-insensitive. 
        /// If the function succeeds, the return value is nonzero.
        /// </summary>
        int delete_section(const wchar_t* section, const std::filesystem::path& path);

        /// <summary>
        /// Returns the key names associated with the section name. The section name is case-insensitive. 
        /// </summary>
        std::vector<std::wstring> get_keys(const wchar_t* section, const std::filesystem::path& path);

        /// <summary>
        /// Returns the key-value pairs associated with the section name. The section name is case-insensitive.
        /// </summary>
        std::vector<std::pair<std::wstring, std::wstring>> get_pairs(const wchar_t* section, const std::filesystem::path& path);

        /// <summary>
        /// Returns the section names.
        /// </summary>
        std::vector<std::wstring> get_sections(const std::filesystem::path& path);

        /// <summary>
        /// Returns the value associated with the key name. The section name is case-insensitive. 
        /// If the function fails, it returns the default value.
        /// </summary>
        unsigned get_value(const wchar_t* section, const wchar_t* key, int defaultValue, const std::filesystem::path& path);

        /// <summary>
        /// Returns the value associated with the key name. The section name is case-insensitive. 
        /// If the function fails, it returns the default value.
        /// </summary>
        std::wstring get_value(const wchar_t* section, const wchar_t* key, const wchar_t* defaultValue, const std::filesystem::path& path);

        /// <summary>
        /// Writes the key-value pair associated with the section name. The section name is case-insensitive. 
        /// If the section name does not exist, it is created. Likewise, if the file does not exist, it is created. 
        /// If the function succeeds, the return value is nonzero.
        /// </summary>
        int write_pair(const wchar_t* section, const wchar_t* key, const wchar_t* value, const std::filesystem::path& path);
    }
}
