#include <filesystem>
#include <ranges>
#include <string>
#include <sstream>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/shaiya/include/CLogConnection.h>
#include <include/shaiya/include/Ini.h>
#include <include/shaiya/include/SLog.h>
#include <include/shaiya/include/Synthesis.h>
#include <util/include/util.h>
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

    Ini ini(path);

    std::vector<std::string> sections;
    ini.getSectionNames(sections);

    for (const auto& section : sections)
    {
        std::vector<Ini::KeyValPair> vec;
        ini.getSection(section, vec);

        if (vec.size() != 8)
            continue;

        auto itemId = std::strtoul(vec[0].value.c_str(), nullptr, 10);
        auto successRate = std::atoi(vec[1].value.c_str());
        successRate = (successRate > 100) ? 100 : successRate;

        Synthesis synthesis{};
        synthesis.successRate = successRate * 100;

        Synthesis::parseMaterial(vec[2].value, synthesis.materialType);
        Synthesis::parseMaterial(vec[3].value, synthesis.materialTypeId);
        Synthesis::parseMaterial(vec[4].value, synthesis.materialCount);

        synthesis.createType = std::atoi(vec[5].value.c_str());
        synthesis.createTypeId = std::atoi(vec[6].value.c_str());
        synthesis.createCount = std::atoi(vec[7].value.c_str());

        auto it = g_synthesis.find(itemId);
        if (it != g_synthesis.end())
            it->second.push_back(synthesis);
        else
            g_synthesis.insert({ itemId, { synthesis } });
    }
}

void Synthesis::parseMaterial(const std::string& text, std::array<UINT8, 24>& output)
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
