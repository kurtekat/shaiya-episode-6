#include <filesystem>
#include <string>
#include <sstream>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "include/shaiya/include/CLogConnection.h"
#include "include/shaiya/include/Ini.h"
#include "include/shaiya/include/SLog.h"
#include "include/shaiya/include/Synthesis.h"
using namespace shaiya;

void Synthesis::init()
{
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

        Synthesis::parseMaterial(kvp[2].second, synthesis.materialType);
        Synthesis::parseMaterial(kvp[3].second, synthesis.materialTypeId);
        Synthesis::parseMaterial(kvp[4].second, synthesis.materialCount);

        synthesis.createType = std::atoi(kvp[5].second.c_str());
        synthesis.createTypeId = std::atoi(kvp[6].second.c_str());
        synthesis.createCount = std::atoi(kvp[7].second.c_str());

        auto it = g_synthesis.find(itemId);
        if (it != g_synthesis.end())
            it->second.push_back(synthesis);
        else
            g_synthesis.insert({ itemId, { synthesis } });
    }
}

void Synthesis::parseMaterial(const std::string& text, std::array<uint8_t, 24>& output)
{
    if (text.empty())
        return;

    std::istringstream iss(text);
    std::vector<int> vec{};
    for (std::string str; std::getline(iss, str, ','); )
        vec.push_back(std::atoi(str.c_str()));

    if (vec.size() != output.size())
        return;

    std::copy(vec.begin(), vec.end(), output.begin());
}
