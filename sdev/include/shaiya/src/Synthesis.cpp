#include <array>
#include <filesystem>
#include <ranges>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "include/shaiya/include/CLogConnection.h"
#include "include/shaiya/include/SLog.h"
#include "include/shaiya/include/Synthesis.h"
using namespace shaiya;

void Synthesis::init()
{
    std::array<char, MAX_PATH> fileName{};
    GetModuleFileNameA(nullptr, fileName.data(), fileName.size());

    std::filesystem::path path(fileName.data());
    path.remove_filename();
    path.append("Data");
    path.append("ChaoticSquare.ini");

    if (!std::filesystem::exists(path))
    {
        SLog::PrintFileDirect(&g_pClientToLog->log, "Synthesis::init : %s does not exist", path.string().c_str());
        return;
    }

    std::error_code ec;
    auto size = std::filesystem::file_size(path, ec);
    if (size == -1)
        return;

    std::vector<char> output(static_cast<size_t>(size));
    auto count = GetPrivateProfileSectionNamesA(output.data(), output.size(), path.string().c_str());
    if (!count)
        return;

    try
    {
        std::istringstream iss(std::string(output.data(), count + 1));
        std::vector<std::string> sections;

        for (std::string str; std::getline(iss, str, '\0'); )
            sections.push_back(str);

        for (const auto& section : sections)
        {
            std::vector<char> vec(INT16_MAX);
            auto count = GetPrivateProfileSectionA(section.c_str(), vec.data(), vec.size(), path.string().c_str());
            if (!count)
                continue;

            std::istringstream iss(std::string(vec.data(), count + 1));
            std::vector<std::pair<std::string, std::string>> kvp;

            for (std::string str; std::getline(iss, str, '\0'); )
            {
                auto offest = str.find_first_of('=');
                if (offest == std::string::npos)
                    continue;

                auto key = str.substr(0, offest);
                auto value = str.substr(offest + 1);
                kvp.push_back({ key, value });
            }

            if (kvp.size() != 8)
                continue;

            auto itemId = std::atoi(kvp[0].second.c_str());
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
    catch (const std::exception& ex)
    {
        SLog::PrintFileDirect(&g_pClientToLog->log, "Synthesis::init : %s", ex.what());
        g_synthesis.clear();
    }
}
