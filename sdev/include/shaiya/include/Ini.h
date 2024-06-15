#pragma once
#include <filesystem>
#include <string>
#include <vector>

namespace shaiya
{
    class Ini
    {
    public:

        Ini(const std::filesystem::path& path)
            : path(path)
        {
        }

        int deleteKey(const std::string& section, const std::string& key);
        int deleteSection(const std::string& section);
        auto getInt(const std::string& section, const std::string& key, int _default);
        void getSection(const std::string& section, std::vector<std::pair<std::string, std::string>>& output);
        void getSectionNames(std::vector<std::string>& output);
        std::string getString(const std::string& section, const std::string& key);
        int writeString(const std::string& section, const std::string& key, const std::string& value);

    private:

        std::filesystem::path path;
    };
}
