#include <filesystem>
#include <sstream>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "ini.h"
using namespace ini;

std::vector<std::pair<std::string, std::string>>
IniHelper::getSectionA(const std::string& sectionName, const std::filesystem::path& fileName)
{
    std::error_code ec;
    auto size = std::filesystem::file_size(fileName, ec);
    if (size == -1)
        return {};

    std::string buffer(static_cast<size_t>(size), 0);
    auto count = GetPrivateProfileSectionA(sectionName.c_str(), buffer.data(), static_cast<DWORD>(buffer.size()), fileName.string().c_str());
    if (!count)
        return {};

    std::vector<std::pair<std::string, std::string>> section;
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

std::vector<std::pair<std::wstring, std::wstring>>
IniHelper::getSectionW(const std::wstring& sectionName, const std::filesystem::path& fileName)
{
    std::error_code ec;
    auto size = std::filesystem::file_size(fileName, ec);
    if (size == -1)
        return {};

    std::wstring buffer(static_cast<size_t>(size), 0);
    auto count = GetPrivateProfileSectionW(sectionName.c_str(), buffer.data(), static_cast<DWORD>(buffer.size()), fileName.c_str());
    if (!count)
        return {};

    std::vector<std::pair<std::wstring, std::wstring>> section;
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

std::vector<std::string> IniHelper::getSectionNamesA(const std::filesystem::path& fileName)
{
    std::error_code ec;
    auto size = std::filesystem::file_size(fileName, ec);
    if (size == -1)
        return {};

    std::string buffer(static_cast<size_t>(size), 0);
    auto count = GetPrivateProfileSectionNamesA(buffer.data(), static_cast<DWORD>(buffer.size()), fileName.string().c_str());
    if (!count)
        return {};

    std::vector<std::string> sectionNames;
    buffer.resize(count);
    std::istringstream iss(buffer);

    for (std::string str; std::getline(iss, str, '\0'); )
        sectionNames.push_back(str);

    return sectionNames;
}

std::vector<std::wstring> IniHelper::getSectionNamesW(const std::filesystem::path& fileName)
{
    std::error_code ec;
    auto size = std::filesystem::file_size(fileName, ec);
    if (size == -1)
        return {};

    std::wstring buffer(static_cast<size_t>(size), 0);
    auto count = GetPrivateProfileSectionNamesW(buffer.data(), static_cast<DWORD>(buffer.size()), fileName.c_str());
    if (!count)
        return {};

    std::vector<std::wstring> sectionNames;
    buffer.resize(count);
    std::wistringstream iss(buffer);

    for (std::wstring str; std::getline(iss, str, L'\0'); )
        sectionNames.push_back(str);

    return sectionNames;
}
