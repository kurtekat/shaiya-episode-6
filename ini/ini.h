#pragma once
#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

namespace ini
{
    class IniHelper
    {
    public:

        using Path = std::filesystem::path;

        static int deleteKey(const wchar_t* sectionName, const wchar_t* keyName, const Path& fileName);
        static int deleteSection(const wchar_t* sectionName, const Path& fileName);
        static uint32_t getInteger(const wchar_t* sectionName, const wchar_t* keyName, int defaultValue, const Path& fileName);
        static std::vector<std::wstring> getKeyNames(const wchar_t* sectionName, const Path& fileName);
        static std::vector<std::pair<std::wstring, std::wstring>> getSection(const wchar_t* sectionName, const Path& fileName);
        static std::vector<std::wstring> getSectionNames(const Path& fileName);
        static std::wstring getString(const wchar_t* sectionName, const wchar_t* keyName, const wchar_t* defaultValue, const Path& fileName);
        static int writeString(const wchar_t* sectionName, const wchar_t* keyName, const wchar_t* value, const Path& fileName);

    };
}
