#include <array>
#include <filesystem>
#include <sstream>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "include/shaiya/include/IniHelper.h"
using namespace shaiya;

std::vector<std::string> IniHelper::getSectionNamesA(const std::filesystem::path fileName)
{
    if (!std::filesystem::exists(fileName))
        return {};

    std::error_code ec;
    auto size = std::filesystem::file_size(fileName, ec);
    if (size == -1)
        return {};

    std::vector<char> output(static_cast<size_t>(size));
    auto count = GetPrivateProfileSectionNamesA(output.data(), output.size(), fileName.string().c_str());
    if (!count)
        return {};

    std::istringstream iss(std::string(output.data(), count + 1));
    std::vector<std::string> sectionNames;

    for (std::string str; std::getline(iss, str, '\0'); )
        sectionNames.push_back(str);

    return sectionNames;
}

std::vector<std::pair<std::string, std::string>> 
IniHelper::getSectionA(const std::string& sectionName, const std::filesystem::path& fileName)
{
    if (!std::filesystem::exists(fileName))
        return {};

    std::vector<char> vec(INT16_MAX);
    auto count = GetPrivateProfileSectionA(sectionName.c_str(), vec.data(), vec.size(), fileName.string().c_str());
    if (!count)
        return {};

    std::istringstream iss(std::string(vec.data(), count + 1));
    std::vector<std::pair<std::string, std::string>> section;

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
