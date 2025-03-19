#pragma once
#include <filesystem>
#include <string>
#include <vector>

namespace ini
{
    using Path = std::filesystem::path;
    using String = std::wstring;

    class IniHelper
    {
    public:

        static int deleteKey(const String& sectionName, const String& keyName, const Path& fileName);
        static int deleteSection(const String& sectionName, const Path& fileName);
        static uint32_t getInteger(const String& sectionName, const String& keyName, int defaultValue, const Path& fileName);
        static std::vector<String> getKeyNames(const String& sectionName, const Path& fileName);
        static std::vector<std::pair<String, String>> getSection(const String& sectionName, const Path& fileName);
        static std::vector<String> getSectionNames(const Path& fileName);
        static String getString(const String& sectionName, const String& keyName, const String& defaultValue, const Path& fileName);
        static int writeString(const String& sectionName, const String& keyName, const String& value, const Path& fileName);

    };
}
