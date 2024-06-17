#include <filesystem>
#include <ranges>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <util/io/Ini.h>
#include "include/shaiya/include/CLogConnection.h"
#include "include/shaiya/include/SLog.h"
#include "include/shaiya/include/Synthesis.h"
using namespace shaiya;

void Synthesis::init()
{
    using namespace util::io;

    std::vector<char> vec(MAX_PATH);
    GetModuleFileNameA(nullptr, vec.data(), vec.size());

    std::filesystem::path path(vec.data());
    path.remove_filename();
    path.append("Data/ItemSynthesis.ini");

    if (!std::filesystem::exists(path))
    {
        SLog::PrintFileDirect(&g_pClientToLog->log, "cannot %s %s: %s", "open", ".\\Data\\ItemSynthesis.ini", "No such file or directory");
        return;
    }

    std::vector<std::string> sections;
    Ini ini(path);
    ini.getSectionNames(sections);

    for (const auto& section : sections)
    {
        std::vector<std::pair<std::string, std::string>> kvp;
        ini.getSection(section, kvp);

        if (kvp.size() != 8)
            continue;

        auto itemId = std::strtoul(kvp[0].second.c_str(), nullptr, 10);
        auto successRate = std::atoi(kvp[1].second.c_str());
        successRate = (successRate > 100) ? 100 : successRate;

        Synthesis synthesis{};
        synthesis.successRate = successRate * 100;

        auto itemList = std::ranges::views::zip(
            synthesis.materialType,
            synthesis.materialTypeId,
            synthesis.materialCount
        );

        std::vector<int> vec1{};
        for (const auto& token : std::views::split(kvp[2].second, ','))
            vec1.push_back(std::atoi(token.data()));

        if (vec1.size() != itemList.size())
            continue;

        std::vector<int> vec2{};
        for (const auto& token : std::views::split(kvp[3].second, ','))
            vec2.push_back(std::atoi(token.data()));

        if (vec2.size() != itemList.size())
            continue;

        std::vector<int> vec3{};
        for (const auto& token : std::views::split(kvp[4].second, ','))
            vec3.push_back(std::atoi(token.data()));

        if (vec3.size() != itemList.size())
            continue;

        for (int i = 0; std::cmp_less(i, itemList.size()); ++i)
        {
            std::get<0>(itemList[i]) = vec1[i];
            std::get<1>(itemList[i]) = vec2[i];
            std::get<2>(itemList[i]) = vec3[i];
        }

        synthesis.createType = std::atoi(kvp[5].second.c_str());
        synthesis.createTypeId = std::atoi(kvp[6].second.c_str());
        synthesis.createCount = std::atoi(kvp[7].second.c_str());

        if (auto it = g_synthesis.find(itemId); it != g_synthesis.end())
            it->second.push_back(synthesis);
        else
            g_synthesis.insert({ itemId, { synthesis } });
    }
}
