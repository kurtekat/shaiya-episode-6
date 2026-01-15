#include <filesystem>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Ini.h"
#include "include/extensions/ranges.hpp"
using namespace shaiya;

std::wstring Ini::GetValueOrDefault(const std::wstring& key, const std::wstring& defaultValue) const
{
    return m_data.contains(key) ? m_data.at(key) : defaultValue;
}

int Ini::GetValueOrDefault(const std::wstring& key, int defaultValue) const
{
    return m_data.contains(key) ? std::stoi(m_data.at(key)) : defaultValue;
}

void Ini::Read()
{
    m_data.clear();

    auto output = GetString(nullptr, nullptr, nullptr);
    auto sections = ext::views::split_to<std::vector<std::wstring>>(output, L'\0');
    if (sections.empty())
        return;

    for (const auto& section : sections)
    {
        if (section.empty())
            continue;

        auto output = GetString(section.c_str(), nullptr, nullptr);
        auto keys = ext::views::split_to<std::vector<std::wstring>>(output, L'\0');
        if (keys.empty())
            continue;

        std::vector<std::pair<std::wstring, std::wstring>> pairs;
        for (const auto& key : keys)
        {
            if (key.empty())
                continue;

            auto value = GetString(section.c_str(), key.c_str(), nullptr);
            pairs.push_back({ key, value });
        }

        for (const auto& pair : pairs)
        {
            // Section:Key
            auto key = section + L":" + pair.first;
            if (m_data.contains(key))
                continue;

            // { Section:Key, Value }
            m_data[key] = pair.second;
        }
    }
}

std::wstring Ini::GetString(const wchar_t* section, const wchar_t* key, const wchar_t* defaultValue) const
{
    size_t size = (!section || !key) ? INT16_MAX : UINT8_MAX;
    if (!defaultValue)
        defaultValue = L"";

    std::wstring output(size, L'\0');
    auto count = GetPrivateProfileStringW(section, key, nullptr, output.data(), output.size(), m_path.c_str());
    if (!count)
        return defaultValue;

    output.resize(count);
    return output;
}
