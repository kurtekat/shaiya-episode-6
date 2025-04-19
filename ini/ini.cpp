#include <cstdint>
#include <filesystem>
#include <sstream>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "ini.h"

int ini::IniHelper::deleteKey(const wchar_t* sectionName, const wchar_t* keyName, const Path& fileName)
{
    return WritePrivateProfileStringW(sectionName, keyName, nullptr, fileName.c_str());
}

int ini::IniHelper::deleteSection(const wchar_t* sectionName, const Path& fileName)
{
    return WritePrivateProfileStringW(sectionName, nullptr, nullptr, fileName.c_str());
}

uint32_t ini::IniHelper::getInteger(const wchar_t* sectionName, const wchar_t* keyName, int defaultValue, const Path& fileName)
{
    return GetPrivateProfileIntW(sectionName, keyName, defaultValue, fileName.c_str());
}

std::vector<std::wstring> ini::IniHelper::getKeyNames(const wchar_t* sectionName, const Path& fileName)
{
    std::vector<std::wstring> vec;
    auto str = getString(sectionName, nullptr, nullptr, fileName);
    if (str.empty())
        return vec;

    std::wistringstream iss(str);
    for (std::wstring str; std::getline(iss, str, L'\0'); )
        vec.push_back(str);

    return vec;
}

std::vector<std::pair<std::wstring, std::wstring>> ini::IniHelper::getSection(const wchar_t* sectionName, const Path& fileName)
{
    std::vector<std::pair<std::wstring, std::wstring>> vec;

    auto keyNames = getKeyNames(sectionName, fileName);
    for (const auto& keyName : keyNames)
    {
        auto value = getString(sectionName, keyName.c_str(), nullptr, fileName);
        vec.push_back({ keyName, value });
    }

    return vec;
}

std::vector<std::wstring> ini::IniHelper::getSectionNames(const Path& fileName)
{
    std::vector<std::wstring> vec;
    auto str = getString(nullptr, nullptr, nullptr, fileName);
    if (str.empty())
        return vec;

    std::wistringstream iss(str);
    for (std::wstring str; std::getline(iss, str, L'\0'); )
        vec.push_back(str);

    return vec;
}

std::wstring ini::IniHelper::getString(const wchar_t* sectionName, const wchar_t* keyName, const wchar_t* defaultValue, const Path& fileName)
{
    if (defaultValue == nullptr)
        defaultValue = L"";

    std::error_code ec;
    auto size = std::filesystem::file_size(fileName, ec);
    if (size == -1)
        return defaultValue;

    if (size > UINT32_MAX)
        size = UINT32_MAX;

    std::wstring buffer(size, 0);
    auto count = GetPrivateProfileStringW(sectionName, keyName, defaultValue, buffer.data(), buffer.size(), fileName.c_str());
    if (!count)
        return defaultValue;

    buffer.resize(count);
    return buffer;
}

int ini::IniHelper::writeString(const wchar_t* sectionName, const wchar_t* keyName, const wchar_t* value, const Path& fileName)
{
    return WritePrivateProfileStringW(sectionName, keyName, value, fileName.c_str());
}
