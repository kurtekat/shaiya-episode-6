#pragma once
#include <filesystem>
#include <string>
#include <vector>

namespace shaiya
{
    class IniHelper
    {
    public:

        /// <summary>
        /// 
        /// </summary>
        /// <param name="fileName"></param>
        /// <returns></returns>
        static std::vector<std::string> getSectionNamesA(const std::filesystem::path fileName);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sectionName"></param>
        /// <param name="fileName"></param>
        /// <returns></returns>
        static std::vector<std::pair<std::string, std::string>> 
            getSectionA(const std::string& sectionName, const std::filesystem::path& fileName);
    };
}
