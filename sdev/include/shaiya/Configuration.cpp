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
#include "SBinaryReader.h"
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

        if (!std::filesystem::exists(path))
            return;

        SBinaryReader reader(path);
        auto recordCount = reader.readUInt32();
        for (size_t i = 0; i < recordCount; ++i)
        {
            ItemSet itemSet{};
            itemSet.id = reader.readUInt16();

            // Discard the name
            auto length = reader.readUInt32();
            reader.ignore(length);

            for (auto&& itemId : itemSet.items)
            {
                auto type = reader.readUInt16();
                auto typeId = reader.readUInt16();
                itemId = (type * 1000) + typeId;
            }

            for (auto&& synergy : itemSet.synergies)
            {
                // e.g., 70,50,0,0,0,20,0,0,0,0,0,0
                auto effects = reader.readString();
                auto rng = std::views::split(effects, ',');
                auto vec = std::ranges::to<std::vector<std::string>>(rng);
                if (vec.size() != synergy.effects.size())
                    continue;

                for (size_t i = 0; i < synergy.effects.size(); ++i)
                    synergy.effects[i] = std::stoi(vec[i]);
            }

            g_itemSets.push_back(itemSet);
        }

        reader.close();
    }
    catch (...)
    {
        g_itemSets.clear();
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
