#include <filesystem>
#include <sstream>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "ini.h"
using namespace ini;

int IniHelper::deleteKeyA(const StringA& sectionName, const StringA& keyName, const Path& fileName)
{
    return WritePrivateProfileStringA(sectionName.c_str(), keyName.c_str(), nullptr, fileName.string().c_str());
}

int IniHelper::deleteKeyW(const StringW& sectionName, const StringW& keyName, const Path& fileName)
{
    return WritePrivateProfileStringW(sectionName.c_str(), keyName.c_str(), nullptr, fileName.c_str());
}

int IniHelper::deleteSectionA(const StringA& sectionName, const Path& fileName)
{
    return WritePrivateProfileStringA(sectionName.c_str(), nullptr, nullptr, fileName.string().c_str());
}

int IniHelper::deleteSectionW(const StringW& sectionName, const Path& fileName)
{
    return WritePrivateProfileStringW(sectionName.c_str(), nullptr, nullptr, fileName.c_str());
}

uint32_t IniHelper::getIntA(const StringA& sectionName, const StringA& keyName, int defaultValue, const Path& fileName)
{
    return GetPrivateProfileIntA(sectionName.c_str(), keyName.c_str(), defaultValue, fileName.string().c_str());
}

uint32_t IniHelper::getIntW(const StringW& sectionName, const StringW& keyName, int defaultValue, const Path& fileName)
{
    return GetPrivateProfileIntW(sectionName.c_str(), keyName.c_str(), defaultValue, fileName.c_str());
}

std::vector<StringA> IniHelper::getKeyNamesA(const StringA& sectionName, const Path& fileName)
{
    std::error_code ec;
    auto fileSize = std::filesystem::file_size(fileName, ec);
    if (fileSize == -1)
        return {};

    if (fileSize > max_buffer_size)
        fileSize = max_buffer_size;

    auto size = static_cast<uint32_t>(fileSize);
    std::string buffer(size, 0);

    auto count = GetPrivateProfileStringA(sectionName.c_str(), nullptr, nullptr, buffer.data(), size, fileName.string().c_str());
    if (!count)
        return {};

    std::vector<StringA> keyNames;
    buffer.resize(count);
    std::istringstream iss(buffer);

    for (std::string str; std::getline(iss, str, '\0'); )
        keyNames.push_back(str);

    return keyNames;
}

std::vector<StringW> IniHelper::getKeyNamesW(const StringW& sectionName, const Path& fileName)
{
    std::error_code ec;
    auto fileSize = std::filesystem::file_size(fileName, ec);
    if (fileSize == -1)
        return {};

    if (fileSize > max_buffer_size)
        fileSize = max_buffer_size;

    auto size = static_cast<uint32_t>(fileSize);
    std::wstring buffer(size, 0);

    auto count = GetPrivateProfileStringW(sectionName.c_str(), nullptr, nullptr, buffer.data(), size, fileName.c_str());
    if (!count)
        return {};

    std::vector<StringW> keyNames;
    buffer.resize(count);
    std::wistringstream iss(buffer);

    for (std::wstring str; std::getline(iss, str, L'\0'); )
        keyNames.push_back(str);

    return keyNames;
}

std::vector<std::pair<StringA, StringA>> IniHelper::getSectionA(const StringA& sectionName, const Path& fileName)
{
    std::error_code ec;
    auto fileSize = std::filesystem::file_size(fileName, ec);
    if (fileSize == -1)
        return {};

    if (fileSize > max_buffer_size)
        fileSize = max_buffer_size;

    auto size = static_cast<uint32_t>(fileSize);
    std::string buffer(size, 0);

    auto count = GetPrivateProfileSectionA(sectionName.c_str(), buffer.data(), size, fileName.string().c_str());
    if (!count)
        return {};

    std::vector<std::pair<StringA, StringA>> section;
    buffer.resize(count);
    std::istringstream iss(buffer);

    for (std::string str; std::getline(iss, str, '\0'); )
    {
        auto offest = str.find_first_of('=');
        if (offest == std::string::npos)
            continue;

        auto key = str.substr(0, offest);
        auto value = str.substr(offest + 1);
        section.push_back({ key, value });
    }

    return section;
}

std::vector<std::pair<StringW, StringW>> IniHelper::getSectionW(const StringW& sectionName, const Path& fileName)
{
    std::error_code ec;
    auto fileSize = std::filesystem::file_size(fileName, ec);
    if (fileSize == -1)
        return {};

    if (fileSize > max_buffer_size)
        fileSize = max_buffer_size;

    auto size = static_cast<uint32_t>(fileSize);
    std::wstring buffer(size, 0);

    auto count = GetPrivateProfileSectionW(sectionName.c_str(), buffer.data(), size, fileName.c_str());
    if (!count)
        return {};

    std::vector<std::pair<StringW, StringW>> section;
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

std::vector<StringA> IniHelper::getSectionNamesA(const Path& fileName)
{
    std::error_code ec;
    auto fileSize = std::filesystem::file_size(fileName, ec);
    if (fileSize == -1)
        return {};

    if (fileSize > max_buffer_size)
        fileSize = max_buffer_size;

    auto size = static_cast<uint32_t>(fileSize);
    std::string buffer(size, 0);

    auto count = GetPrivateProfileSectionNamesA(buffer.data(), size, fileName.string().c_str());
    if (!count)
        return {};

    std::vector<StringA> sectionNames;
    buffer.resize(count);
    std::istringstream iss(buffer);

    for (std::string str; std::getline(iss, str, '\0'); )
        sectionNames.push_back(str);

    return sectionNames;
}

std::vector<StringW> IniHelper::getSectionNamesW(const Path& fileName)
{
    std::error_code ec;
    auto fileSize = std::filesystem::file_size(fileName, ec);
    if (fileSize == -1)
        return {};

    if (fileSize > max_buffer_size)
        fileSize = max_buffer_size;

    auto size = static_cast<uint32_t>(fileSize);
    std::wstring buffer(size, 0);

    auto count = GetPrivateProfileSectionNamesW(buffer.data(), size, fileName.c_str());
    if (!count)
        return {};

    std::vector<StringW> sectionNames;
    buffer.resize(count);
    std::wistringstream iss(buffer);

    for (std::wstring str; std::getline(iss, str, L'\0'); )
        sectionNames.push_back(str);

    return sectionNames;
}

StringA IniHelper::getStringA(const StringA& sectionName, const StringA& keyName, const StringA& defaultValue, const Path& fileName)
{
    std::error_code ec;
    auto fileSize = std::filesystem::file_size(fileName, ec);
    if (fileSize == -1)
        return defaultValue;

    if (fileSize > max_buffer_size)
        fileSize = max_buffer_size;

    auto size = static_cast<uint32_t>(fileSize);
    std::string buffer(size, 0);

    auto count = GetPrivateProfileStringA(sectionName.c_str(), keyName.c_str(), defaultValue.c_str(), buffer.data(), size, fileName.string().c_str());
    if (!count)
        return defaultValue;

    buffer.resize(count);
    return buffer;
}

StringW IniHelper::getStringW(const StringW& sectionName, const StringW& keyName, const StringW& defaultValue, const Path& fileName)
{
    std::error_code ec;
    auto fileSize = std::filesystem::file_size(fileName, ec);
    if (fileSize == -1)
        return defaultValue;

    if (fileSize > max_buffer_size)
        fileSize = max_buffer_size;

    auto size = static_cast<uint32_t>(fileSize);
    std::wstring buffer(size, 0);

    auto count = GetPrivateProfileStringW(sectionName.c_str(), keyName.c_str(), defaultValue.c_str(), buffer.data(), size, fileName.c_str());
    if (!count)
        return defaultValue;

    buffer.resize(count);
    return buffer;
}

int IniHelper::writeStringA(const StringA& sectionName, const StringA& keyName, const StringA& value, const Path& fileName)
{
    return WritePrivateProfileStringA(sectionName.c_str(), keyName.c_str(), value.c_str(), fileName.string().c_str());
}

int IniHelper::writeStringW(const StringW& sectionName, const StringW& keyName, const StringW& value, const Path& fileName)
{
    return WritePrivateProfileStringW(sectionName.c_str(), keyName.c_str(), value.c_str(), fileName.c_str());
}
