#include <filesystem>
#include <fstream>
#include <map>
#include <ranges>
#include <string>
#include <tuple>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h> 
#include <util/ini/ini.h>
#include "Configuration.h"
#include "ItemRemake.h"
#include "PathHelper.h"
#include "RewardItem.h"
#include "Synergy.h"
#include "Synthesis.h"
using namespace shaiya;

void Configuration::Init()
{
    std::wstring buffer(INT16_MAX, 0);
    auto count = GetModuleFileNameW(nullptr, buffer.data(), INT16_MAX);
    if (!count)
        return;

    auto first = buffer.begin();
    auto last = first + count;
    Configuration::m_root.assign(first, last).remove_filename();
}

void Configuration::LoadItemRemake4()
{
    try
    {
        std::filesystem::path path(m_root);
        PathHelper::combine(path, "Data", "ItemRemake4.ini");

        if (!std::filesystem::exists(path))
            return;

        for (const auto& section : util::ini::get_sections(path))
        {
            auto pairs = util::ini::get_pairs(section.c_str(), path);
            if (pairs.size() != 5)
                continue;

            ItemRemake remake{};
            remake.items[0] = std::stoi(pairs[0].second);
            remake.items[1] = std::stoi(pairs[1].second);
            remake.items[2] = std::stoi(pairs[2].second);
            remake.newItemType = std::stoi(pairs[3].second);
            remake.newItemTypeId = std::stoi(pairs[4].second);
            g_itemRemake4.push_back(remake);
        }
    }
    catch (...)
    {
        g_itemRemake4.clear();
    }
}

void Configuration::LoadItemRemake5()
{
    try
    {
        std::filesystem::path path(m_root);
        PathHelper::combine(path, "Data", "ItemRemake5.ini");

        if (!std::filesystem::exists(path))
            return;

        for (const auto& section : util::ini::get_sections(path))
        {
            auto pairs = util::ini::get_pairs(section.c_str(), path);
            if (pairs.size() != 5)
                continue;

            ItemRemake remake{};
            remake.items[0] = std::stoi(pairs[0].second);
            remake.items[1] = std::stoi(pairs[1].second);
            remake.items[2] = std::stoi(pairs[2].second);
            remake.newItemType = std::stoi(pairs[3].second);
            remake.newItemTypeId = std::stoi(pairs[4].second);
            g_itemRemake5.push_back(remake);
        }
    }
    catch (...)
    {
        g_itemRemake5.clear();
    }
}

void Configuration::LoadItemSetData()
{
    try
    {
        std::filesystem::path path(m_root);
        PathHelper::combine(path, "Data", "SetItem.SData");

        std::ifstream sdata(path, std::ios::binary);
        if (!sdata)
            return;

        uint32_t recordCount{};
        sdata.read(reinterpret_cast<char*>(&recordCount), 4);

        for (int i = 0; std::cmp_less(i, recordCount); ++i)
        {
            uint16_t id{};
            sdata.read(reinterpret_cast<char*>(&id), 2);

            Synergy synergy{};
            synergy.id = id;

            uint32_t nameLength{};
            sdata.read(reinterpret_cast<char*>(&nameLength), 4);
            sdata.ignore(nameLength);

            for (auto&& itemId : synergy.set)
            {
                uint16_t type{}, typeId{};
                sdata.read(reinterpret_cast<char*>(&type), 2);
                sdata.read(reinterpret_cast<char*>(&typeId), 2);
                itemId = (type * 1000) + typeId;
            }

            for (auto&& effect : synergy.effects)
            {
                uint32_t textLength{};
                sdata.read(reinterpret_cast<char*>(&textLength), 4);

                // e.g., 70,50,0,0,0,20,0,0,0,0,0,0
                std::string text(textLength, '\0');
                sdata.read(text.data(), text.size());

                auto rng = std::views::split(text, ',');
                auto vec = std::ranges::to<std::vector<std::string>>(rng);
                if (vec.size() != effect.size())
                    continue;

                for (int i = 0; std::cmp_less(i, effect.size()); ++i)
                    effect[i] = std::stoi(vec[i]);
            }

            g_synergies.push_back(synergy);
        }

        sdata.close();
    }
    catch (...)
    {
        g_synergies.clear();
    }
}

void Configuration::LoadItemSynthesis()
{
    try
    {
        std::filesystem::path path(m_root);
        PathHelper::combine(path, "Data", "ChaoticSquare.ini");

        if (!std::filesystem::exists(path))
            return;

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

            auto rng1 = std::views::split(pairs[2].second, L',');
            auto vec1 = std::ranges::to<std::vector<std::wstring>>(rng1);
            if (vec1.size() != itemList.size())
                continue;

            auto rng2 = std::views::split(pairs[3].second, L',');
            auto vec2 = std::ranges::to<std::vector<std::wstring>>(rng2);
            if (vec2.size() != itemList.size())
                continue;

            auto rng3 = std::views::split(pairs[4].second, L',');
            auto vec3 = std::ranges::to<std::vector<std::wstring>>(rng3);
            if (vec3.size() != itemList.size())
                continue;

            for (int i = 0; std::cmp_less(i, itemList.size()); ++i)
            {
                std::get<0>(itemList[i]) = std::stoi(vec1[i]);
                std::get<1>(itemList[i]) = std::stoi(vec2[i]);
                std::get<2>(itemList[i]) = std::stoi(vec3[i]);
            }

            synthesis.newItemType = std::stoi(pairs[5].second);
            synthesis.newItemTypeId = std::stoi(pairs[6].second);
            synthesis.newItemCount = std::stoi(pairs[7].second);

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

void Configuration::LoadRewardItemEvent()
{
    try
    {
        std::filesystem::path path(m_root);
        PathHelper::combine(path, "Data", "RewardItem.ini");

        if (!std::filesystem::exists(path))
            return;

        for (const auto& section : util::ini::get_sections(path))
        {
            auto pairs = util::ini::get_pairs(section.c_str(), path);
            if (pairs.size() != 4)
                continue;

            auto delay = std::stoi(pairs[0].second);
            if (delay <= 0)
                continue;

            RewardItem item{};
            item.delay = std::chrono::minutes(delay);
            item.type = std::stoi(pairs[1].second);
            item.typeId = std::stoi(pairs[2].second);
            item.count = std::stoi(pairs[3].second);
            g_rewardItems.push_back(item);

            if (g_rewardItems.size() == RewardItemEvent::maxItemCount)
                break;
        }
    }
    catch (...)
    {
        g_rewardItems.clear();
    }
}
