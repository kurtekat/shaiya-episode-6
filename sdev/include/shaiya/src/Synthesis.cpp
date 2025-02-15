#include <array>
#include <filesystem>
#include <ranges>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <util/util.h>
#include "include/shaiya/include/IniHelper.h"
#include "include/shaiya/include/Synthesis.h"
using namespace shaiya;

void Synthesis::init()
{
    try
    {
        std::array<char, MAX_PATH> fileName{};
        GetModuleFileNameA(nullptr, fileName.data(), fileName.size());

        std::filesystem::path path(fileName.data());
        path.remove_filename();
        path.append("Data");
        path.append("ChaoticSquare.ini");

        auto sectionNames = IniHelper::getSectionNamesA(path);
        for (const auto& sectionName : sectionNames)
        {
            auto kvp = IniHelper::getSectionA(sectionName, path);
            if (kvp.size() != 8)
                continue;

            auto itemId = util::atoi(kvp[0].second);
            auto successRate = util::atoi(kvp[1].second);
            successRate = (successRate > 100) ? 100 : successRate;

            Synthesis synthesis{};
            synthesis.successRate = successRate * 100;

            auto itemList = std::ranges::views::zip(
                synthesis.materialType,
                synthesis.materialTypeId,
                synthesis.materialCount
            );

            auto vec1 = util::split(kvp[2].second, ',');
            if (vec1.size() != itemList.size())
                continue;

            auto vec2 = util::split(kvp[3].second, ',');
            if (vec2.size() != itemList.size())
                continue;

            auto vec3 = util::split(kvp[4].second, ',');
            if (vec3.size() != itemList.size())
                continue;

            for (int i = 0; std::cmp_less(i, itemList.size()); ++i)
            {
                std::get<0>(itemList[i]) = util::atoi(vec1[i]);
                std::get<1>(itemList[i]) = util::atoi(vec2[i]);
                std::get<2>(itemList[i]) = util::atoi(vec3[i]);
            }

            synthesis.createType = util::atoi(kvp[5].second);
            synthesis.createTypeId = util::atoi(kvp[6].second);
            synthesis.createCount = util::atoi(kvp[7].second);

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
