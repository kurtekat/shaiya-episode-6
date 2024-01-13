#include <limits>
#include <sstream>
#include <string>
#include <vector>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <uchar.h>

#include <include/shaiya/include/Ini.h>
using namespace shaiya;

auto Ini::getInt(const std::string& section, const std::string& key, int _default)
{
    return GetPrivateProfileIntA(section.c_str(), key.c_str(), _default, this->path.string().c_str());
}

std::string Ini::getString(const std::string& section, const std::string& key)
{
    std::vector<char> vec(std::numeric_limits<std::uint8_t>::max());
    auto count = GetPrivateProfileStringA(section.c_str(), key.c_str(), nullptr, vec.data(), vec.size(), this->path.string().c_str());
    return std::string(vec.data(), count);
}

void Ini::getSection(const std::string& section, std::vector<KeyValPair>& output)
{
    std::vector<char> vec(std::numeric_limits<short>::max());
    auto count = GetPrivateProfileSectionA(section.c_str(), vec.data(), vec.size(), this->path.string().c_str());
    if (!count)
        return;

    auto str = std::string(vec.data(), count);
    std::istringstream iss(str);

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

void Ini::getSectionNames(std::vector<std::string>& output)
{
    std::vector<char> vec(std::numeric_limits<short>::max());
    auto count = GetPrivateProfileSectionNamesA(vec.data(), vec.size(), this->path.string().c_str());
    if (!count)
        return;

    auto str = std::string(vec.data(), count);
    std::istringstream iss(str);

    for (std::string str; std::getline(iss, str, '\0'); )
        output.push_back(str);
}

int Ini::writeString(const std::string& section, const std::string& key, const std::string& value)
{
    return WritePrivateProfileStringA(section.c_str(), key.c_str(), value.c_str(), this->path.string().c_str());
}
