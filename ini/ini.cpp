#include <filesystem>
#include <sstream>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "ini.h"
using namespace ini;

int IniHelper::deleteKey(const String& sectionName, const String& keyName, const Path& fileName)
{
    return WritePrivateProfileStringW(sectionName.c_str(), keyName.c_str(), nullptr, fileName.c_str());
}

int IniHelper::deleteSection(const String& sectionName, const Path& fileName)
{
    return WritePrivateProfileStringW(sectionName.c_str(), nullptr, nullptr, fileName.c_str());
}

uint32_t IniHelper::getInteger(const String& sectionName, const String& keyName, int defaultValue, const Path& fileName)
{
    return GetPrivateProfileIntW(sectionName.c_str(), keyName.c_str(), defaultValue, fileName.c_str());
}

std::vector<String> IniHelper::getKeyNames(const String& sectionName, const Path& fileName)
{
    std::error_code ec;
    auto fileSize = std::filesystem::file_size(fileName, ec);
    if (fileSize == -1)
        return {};

    if (fileSize > UINT32_MAX)
        fileSize = UINT32_MAX;

    std::wstring buffer(fileSize, 0);
    auto count = GetPrivateProfileStringW(sectionName.c_str(), nullptr, nullptr, buffer.data(), buffer.size(), fileName.c_str());
    if (!count)
        return {};

    std::vector<String> keyNames;
    buffer.resize(count);

    std::wistringstream iss(buffer);
    for (std::wstring str; std::getline(iss, str, L'\0'); )
        keyNames.push_back(str);

    return keyNames;
}

std::vector<std::pair<String, String>> IniHelper::getSection(const String& sectionName, const Path& fileName)
{
    std::error_code ec;
    auto fileSize = std::filesystem::file_size(fileName, ec);
    if (fileSize == -1)
        return {};

    if (fileSize > UINT32_MAX)
        fileSize = UINT32_MAX;

    std::wstring buffer(fileSize, 0);
    auto count = GetPrivateProfileSectionW(sectionName.c_str(), buffer.data(), buffer.size(), fileName.c_str());
    if (!count)
        return {};

    std::vector<std::pair<String, String>> section;
    buffer.resize(count);

    std::wistringstream iss(buffer);
    for (std::wstring str; std::getline(iss, str, L'\0'); )
    {
        auto offest = str.find_first_of(L'=');
        if (offest == std::wstring::npos)
            continue;

        auto key = str.substr(0, offest);
        auto value = str.substr(offest + 1);
        section.push_back({ key, value });
    }

    return section;
}

std::vector<String> IniHelper::getSectionNames(const Path& fileName)
{
    std::error_code ec;
    auto fileSize = std::filesystem::file_size(fileName, ec);
    if (fileSize == -1)
        return {};

    if (fileSize > UINT32_MAX)
        fileSize = UINT32_MAX;

    std::wstring buffer(fileSize, 0);
    auto count = GetPrivateProfileSectionNamesW(buffer.data(), buffer.size(), fileName.c_str());
    if (!count)
        return {};

    std::vector<String> sectionNames;
    buffer.resize(count);

    std::wistringstream iss(buffer);
    for (std::wstring str; std::getline(iss, str, L'\0'); )
        sectionNames.push_back(str);

    return sectionNames;
}

String IniHelper::getString(const String& sectionName, const String& keyName, const String& defaultValue, const Path& fileName)
{
    std::error_code ec;
    auto fileSize = std::filesystem::file_size(fileName, ec);
    if (fileSize == -1)
        return defaultValue;

    if (fileSize > UINT32_MAX)
        fileSize = UINT32_MAX;

    std::wstring buffer(fileSize, 0);
    auto count = GetPrivateProfileStringW(sectionName.c_str(), keyName.c_str(), defaultValue.c_str(), buffer.data(), buffer.size(), fileName.c_str());
    if (!count)
        return defaultValue;

    buffer.resize(count);
    return buffer;
}

int IniHelper::writeString(const String& sectionName, const String& keyName, const String& value, const Path& fileName)
{
    return WritePrivateProfileStringW(sectionName.c_str(), keyName.c_str(), value.c_str(), fileName.c_str());
}
