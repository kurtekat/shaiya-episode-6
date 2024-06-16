#include <sstream>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Ini.h"

int util::io::Ini::deleteKey(const std::string& section, const std::string& key)
{
    return WritePrivateProfileStringA(section.c_str(), key.c_str(), nullptr, this->path.string().c_str());
}

int util::io::Ini::deleteSection(const std::string& section)
{
    return WritePrivateProfileStringA(section.c_str(), nullptr, nullptr, this->path.string().c_str());
}

unsigned int util::io::Ini::getInt(const std::string& section, const std::string& key, int _default)
{
    return GetPrivateProfileIntA(section.c_str(), key.c_str(), _default, this->path.string().c_str());
}

std::string util::io::Ini::getString(const std::string& section, const std::string& key, const char* _default)
{
    auto size = this->size();
    if (size == -1)
        return (!_default) ? "" : _default;

    std::vector<char> vec(static_cast<std::size_t>(size));
    auto count = GetPrivateProfileStringA(section.c_str(), key.c_str(), _default, vec.data(), vec.size(), this->path.string().c_str());
    return std::string(vec.data(), count + 1);
}

void util::io::Ini::getSection(const std::string& section, std::vector<std::pair<std::string, std::string>>& output)
{
    auto size = this->size();
    if (size == -1)
        return;

    std::vector<char> vec(static_cast<std::size_t>(size));
    auto count = GetPrivateProfileSectionA(section.c_str(), vec.data(), vec.size(), this->path.string().c_str());
    if (!count)
        return;

    std::istringstream iss(std::string(vec.data(), count + 1));
    for (std::string str; std::getline(iss, str, '\0'); )
    {
        auto offest = str.find_first_of('=');
        if (offest == std::string::npos)
            continue;

        auto key = str.substr(0, offest);
        auto value = str.substr(offest + 1);
        output.push_back({ key, value });
    }
}

void util::io::Ini::getSectionNames(std::vector<std::string>& output)
{
    auto size = this->size();
    if (size == -1)
        return;

    std::vector<char> vec(static_cast<std::size_t>(size));
    auto count = GetPrivateProfileSectionNamesA(vec.data(), vec.size(), this->path.string().c_str());
    if (!count)
        return;

    std::istringstream iss(std::string(vec.data(), count + 1));
    for (std::string str; std::getline(iss, str, '\0'); )
        output.push_back(str);
}

int util::io::Ini::writeString(const std::string& section, const std::string& key, const std::string& value)
{
    return WritePrivateProfileStringA(section.c_str(), key.c_str(), value.c_str(), this->path.string().c_str());
}
