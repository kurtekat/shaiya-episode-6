#include <filesystem>
#include <ranges>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <ini/ini.h>
#include <util/util.h>
#include "include/shaiya/include/Synthesis.h"
using namespace shaiya;

void Synthesis::init()
{
    try
    {
        std::wstring buffer(INT16_MAX, 0);
        if (!GetModuleFileNameW(nullptr, buffer.data(), INT16_MAX))
            return;

        std::filesystem::path path(buffer);
        path.remove_filename();
        path.append("Data");
        path.append("ChaoticSquare.ini");

        auto sectionNames = ini::IniHelper::getSectionNames(path);
        for (const auto& sectionName : sectionNames)
        {
            auto kvp = ini::IniHelper::getSection(sectionName.c_str(), path);
            if (kvp.size() != 8)
                continue;

            auto itemId = std::stoi(kvp[0].second);
            auto successRate = std::stoi(kvp[1].second);
            successRate = (successRate > 100) ? 100 : successRate;

            Synthesis synthesis{};
            synthesis.successRate = successRate * 100;

            auto itemList = std::ranges::views::zip(
                synthesis.materialType,
                synthesis.materialTypeId,
                synthesis.materialCount
            );

            auto vec1 = util::split(kvp[2].second, L',');
            if (vec1.size() != itemList.size())
                continue;

            auto vec2 = util::split(kvp[3].second, L',');
            if (vec2.size() != itemList.size())
                continue;

            auto vec3 = util::split(kvp[4].second, L',');
            if (vec3.size() != itemList.size())
                continue;

            for (int i = 0; std::cmp_less(i, itemList.size()); ++i)
            {
                std::get<0>(itemList[i]) = std::stoi(vec1[i]);
                std::get<1>(itemList[i]) = std::stoi(vec2[i]);
                std::get<2>(itemList[i]) = std::stoi(vec3[i]);
            }

            synthesis.createType = std::stoi(kvp[5].second);
            synthesis.createTypeId = std::stoi(kvp[6].second);
            synthesis.createCount = std::stoi(kvp[7].second);

            if (auto it = g_synthesis.find(itemId); it != g_synthesis.end())
                it->second.push_back(synthesis);
            else
                g_synthesis.insert({ itemId, { synthesis } });
        }
    }
    catch (...)
    {
        g_synthesis.clear();
    }
}
