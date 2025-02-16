#pragma once
#include <filesystem>
#include <string>
#include <vector>

namespace ini
{
    class IniHelper
    {
    public:

        /// <summary>
    /// 
    /// </summary>
    /// <param name="sectionName"></param>
    /// <param name="fileName"></param>
    /// <returns></returns>
        static std::vector<std::pair<std::string, std::string>>
            getSectionA(const std::string& sectionName, const std::filesystem::path& fileName);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sectionName"></param>
        /// <param name="fileName"></param>
        /// <returns></returns>
        static std::vector<std::pair<std::wstring, std::wstring>>
            getSectionW(const std::wstring& sectionName, const std::filesystem::path& fileName);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="fileName"></param>
        /// <returns></returns>
        static std::vector<std::string> getSectionNamesA(const std::filesystem::path& fileName);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="fileName"></param>
        /// <returns></returns>
        static std::vector<std::wstring> getSectionNamesW(const std::filesystem::path& fileName);
    };
}
