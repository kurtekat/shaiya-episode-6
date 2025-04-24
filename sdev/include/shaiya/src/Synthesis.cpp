#include <filesystem>
#include <ranges>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <util/ini/ini.h>
#include <util/string/string.hpp>
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

        for (const auto& section : util::ini::get_sections(path))
        {
            auto pairs = util::ini::get_pairs(section.c_str(), path);
            if (pairs.size() != 8)
                continue;

            auto itemId = std::stoi(pairs[0].second);
            auto successRate = std::stoi(pairs[1].second);
            successRate = (successRate > 100) ? 100 : successRate;

            Synthesis synthesis{};
            synthesis.successRate = successRate * 100;

            auto itemList = std::views::zip(
                synthesis.materialType,
                synthesis.materialTypeId,
                synthesis.materialCount
            );

            auto vec1 = util::string::split(pairs[2].second, L',');
            if (vec1.size() != itemList.size())
                continue;

            auto vec2 = util::string::split(pairs[3].second, L',');
            if (vec2.size() != itemList.size())
                continue;

            auto vec3 = util::string::split(pairs[4].second, L',');
            if (vec3.size() != itemList.size())
                continue;

            for (int i = 0; std::cmp_less(i, itemList.size()); ++i)
            {
                std::get<0>(itemList[i]) = std::stoi(vec1[i]);
                std::get<1>(itemList[i]) = std::stoi(vec2[i]);
                std::get<2>(itemList[i]) = std::stoi(vec3[i]);
            }

            synthesis.createType = std::stoi(pairs[5].second);
            synthesis.createTypeId = std::stoi(pairs[6].second);
            synthesis.createCount = std::stoi(pairs[7].second);

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
