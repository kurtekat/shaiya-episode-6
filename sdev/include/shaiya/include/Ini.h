#pragma once
#include <filesystem>
#include <string>
#include <vector>

namespace shaiya
{
    class Ini
    {
    public:

        struct KeyValPair
        {
            std::string key;
            std::string value;
        };

        Ini(const std::filesystem::path& path)
            : path(path)
        {
        }

        auto getInt(const std::string& section, const std::string& key, int _default);
        std::string getString(const std::string& section, const std::string& key);
        void getSection(const std::string& section, std::vector<KeyValPair>& output);
        void getSectionNames(std::vector<std::string>& output);
        int writeString(const std::string& section, const std::string& key, const std::string& value);

    private:

        std::filesystem::path path;
    };
}
