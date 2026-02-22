#include <filesystem>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <extensions/include/string.hpp>
#include "Ini.h"
using namespace shaiya;

Ini Ini::Parse(const std::filesystem::path& path)
{
    std::wifstream stream(path);
    return Parse(stream);
}

Ini Ini::Parse(std::wifstream& stream)
{
    std::wstringstream iss;
    iss << stream.rdbuf();
    return Parse(iss);
}

Ini Ini::Parse(const std::wstring& rawData)
{
    std::wstringstream iss(rawData);
    return Parse(iss);
}

// Credit: Microsoft.Extensions.Configuration.Ini
Ini Ini::Parse(std::wstringstream& rawData)
{
    Ini ini;
    std::wstring rawLine;
    std::wstring section;

    while (std::getline(rawData, rawLine))
    {
        auto line = ext::string::trim_copy(rawLine);
        if (line.empty())
            continue;

        if (line.starts_with(L';') || line.starts_with(L'#') || line.starts_with(L'/'))
            continue;

        if (line.starts_with(L'[') && line.ends_with(L']'))
        {
            section = ext::string::trim_copy(line.substr(1, line.length() - 2));
            section += L':';
            continue;
        }

        auto offset = line.find(L'=');
        if (offset == std::wstring::npos)
            continue;

        // { Section:Key, Value }
        auto key = section + ext::string::trim_copy(line.substr(0, offset));
        auto value = ext::string::trim_copy(line.substr(offset + 1));

        if (value.length() > 1 && value.starts_with(L'"') && value.ends_with(L'"'))
            value = value.substr(1, value.length() - 2);

        if (ini.data.contains(key))
            continue;

        ini.data[key] = value;
    }

    return ini;
}

std::wstring Ini::GetValueOrDefault(const std::wstring& key, const std::wstring& defaultValue) const
{
    return data.contains(key) ? data.at(key) : defaultValue;
}

int Ini::GetValueOrDefault(const std::wstring& key, int defaultValue) const
{
    return data.contains(key) ? std::stoi(data.at(key)) : defaultValue;
}
