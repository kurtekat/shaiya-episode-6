#pragma once
#include <filesystem>
#include <string>
#include <vector>

namespace ini
{
    using Path = std::filesystem::path;
    using StringA = std::string;
    using StringW = std::wstring;

    class IniHelper
    {
    public:

        static int deleteKeyA(const StringA& sectionName, const StringA& keyName, const Path& fileName);
        static int deleteKeyW(const StringW& sectionName, const StringW& keyName, const Path& fileName);
        static int deleteSectionA(const StringA& sectionName, const Path& fileName);
        static int deleteSectionW(const StringW& sectionName, const Path& fileName);
        static uint32_t getIntA(const StringA& sectionName, const StringA& keyName, int defaultValue, const Path& fileName);
        static uint32_t getIntW(const StringW& sectionName, const StringW& keyName, int defaultValue, const Path& fileName);
        static std::vector<StringA> getKeyNamesA(const StringA& sectionName, const Path& fileName);
        static std::vector<StringW> getKeyNamesW(const StringW& sectionName, const Path& fileName);
        static std::vector<std::pair<StringA, StringA>> getSectionA(const StringA& sectionName, const Path& fileName);
        static std::vector<std::pair<StringW, StringW>> getSectionW(const StringW& sectionName, const Path& fileName);
        static std::vector<StringA> getSectionNamesA(const Path& fileName);
        static std::vector<StringW> getSectionNamesW(const Path& fileName);
        static StringA getStringA(const StringA& sectionName, const StringA& keyName, const StringA& defaultValue, const Path& fileName);
        static StringW getStringW(const StringW& sectionName, const StringW& keyName, const StringW& defaultValue, const Path& fileName);
        static int writeStringA(const StringA& sectionName, const StringA& keyName, const StringA& value, const Path& fileName);
        static int writeStringW(const StringW& sectionName, const StringW& keyName, const StringW& value, const Path& fileName);

    private:

        static constexpr uint32_t max_buffer_size = UINT32_MAX;
    };
}
