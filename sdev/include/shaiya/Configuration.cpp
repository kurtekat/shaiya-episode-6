#include <algorithm>
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
#include <shaiya/include/network/game/RewardItemUnit.h>
#include "include/extensions/filesystem.hpp"
#include "Configuration.h"
#include "ItemInfo.h"
#include "ItemRemake.h"
#include "ItemSynthesis.h"
#include "RewardItem.h"
#include "SBinaryReader.h"
#include "Synergy.h"
using namespace shaiya;

void Configuration::Init()
{
    std::wstring buffer(INT16_MAX, 0);
    auto count = GetModuleFileNameW(nullptr, buffer.data(), INT16_MAX);
    if (!count)
        return;

    auto first = buffer.begin();
    auto last = first + count;
    m_root.assign(first, last).remove_filename();
}

void Configuration::LoadItemRemake4()
{
    try
    {
        std::filesystem::path path(m_root);
        ext::filesystem::combine(path, "Data", "ItemRemake4.ini");

        if (!std::filesystem::exists(path))
            return;

        auto sections = util::ini::get_sections(path);
        for (const auto& section : sections)
        {
            auto pairs = util::ini::get_pairs(section.c_str(), path);
            if (pairs.size() != 5)
                continue;

            auto itemId1 = std::stoi(pairs[0].second);
            if (itemId1 < ItemId_MIN || itemId1 > ItemId_MAX)
                continue;

            auto itemId2 = std::stoi(pairs[1].second);
            if (itemId2 < ItemId_MIN || itemId2 > ItemId_MAX)
                continue;

            auto itemId3 = std::stoi(pairs[2].second);
            if (itemId3 < ItemId_MIN || itemId3 > ItemId_MAX)
                continue;

            auto type = std::stoi(pairs[3].second);
            if (!std::in_range<uint8_t>(type))
                continue;

            auto typeId = std::stoi(pairs[4].second);
            if (!std::in_range<uint8_t>(typeId))
                continue;

            ItemRemake remake{};
            remake.items[0] = itemId1;
            remake.items[1] = itemId2;
            remake.items[2] = itemId3;
            remake.newItemType = type;
            remake.newItemTypeId = typeId;
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
        ext::filesystem::combine(path, "Data", "ItemRemake5.ini");

        if (!std::filesystem::exists(path))
            return;

        auto sections = util::ini::get_sections(path);
        for (const auto& section : sections)
        {
            auto pairs = util::ini::get_pairs(section.c_str(), path);
            if (pairs.size() != 5)
                continue;

            auto itemId1 = std::stoi(pairs[0].second);
            if (itemId1 < ItemId_MIN || itemId1 > ItemId_MAX)
                continue;

            auto itemId2 = std::stoi(pairs[1].second);
            if (itemId2 < ItemId_MIN || itemId2 > ItemId_MAX)
                continue;

            auto itemId3 = std::stoi(pairs[2].second);
            if (itemId3 < ItemId_MIN || itemId3 > ItemId_MAX)
                continue;

            auto type = std::stoi(pairs[3].second);
            if (!std::in_range<uint8_t>(type))
                continue;

            auto typeId = std::stoi(pairs[4].second);
            if (!std::in_range<uint8_t>(typeId))
                continue;

            ItemRemake remake{};
            remake.items[0] = itemId1;
            remake.items[1] = itemId2;
            remake.items[2] = itemId3;
            remake.newItemType = type;
            remake.newItemTypeId = typeId;
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
        ext::filesystem::combine(path, "Data", "SetItem.SData");

        if (!std::filesystem::exists(path))
            return;

        SBinaryReader reader(path);

        auto itemSetCount = reader.readUInt32();
        for (size_t i = 0; i < itemSetCount; ++i)
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

                auto value = (type * 1000) + typeId;
                if (value >= ItemId_MIN && value <= ItemId_MAX)
                    itemId = value;
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
        ext::filesystem::combine(path, "Data", "ChaoticSquare.ini");

        if (!std::filesystem::exists(path))
            return;

        auto sections = util::ini::get_sections(path);
        for (const auto& section : sections)
        {
            auto pairs = util::ini::get_pairs(section.c_str(), path);
            if (pairs.size() != 8)
                continue;

            auto itemId = std::stoi(pairs[0].second);
            if (itemId < ItemId_MIN || itemId > ItemId_MAX)
                continue;

            auto successRate = std::stoi(pairs[1].second);
            successRate = std::clamp(successRate, 1, 100);

            ItemSynthesis synthesis{};
            synthesis.successRate = successRate * 100;

            auto view = std::views::zip(
                synthesis.materialType,
                synthesis.materialTypeId,
                synthesis.materialCount
            );

            auto rng1 = std::views::split(pairs[2].second, L',');
            auto vec1 = std::ranges::to<std::vector<std::wstring>>(rng1);
            if (vec1.size() != view.size())
                continue;

            auto rng2 = std::views::split(pairs[3].second, L',');
            auto vec2 = std::ranges::to<std::vector<std::wstring>>(rng2);
            if (vec2.size() != view.size())
                continue;

            auto rng3 = std::views::split(pairs[4].second, L',');
            auto vec3 = std::ranges::to<std::vector<std::wstring>>(rng3);
            if (vec3.size() != view.size())
                continue;

            for (size_t i = 0; i < view.size(); ++i)
            {
                auto type = std::stoi(vec1[i]);
                if (!std::in_range<uint8_t>(type))
                    continue;

                auto typeId = std::stoi(vec2[i]);
                if (!std::in_range<uint8_t>(typeId))
                    continue;

                auto count = std::stoi(vec3[i]);
                if (!std::in_range<uint8_t>(count))
                    continue;

                std::get<0>(view[i]) = type;
                std::get<1>(view[i]) = typeId;
                std::get<2>(view[i]) = count;
            }

            auto type = std::stoi(pairs[5].second);
            if (!std::in_range<uint8_t>(type))
                continue;

            auto typeId = std::stoi(pairs[6].second);
            if (!std::in_range<uint8_t>(typeId))
                continue;

            auto count = std::stoi(pairs[7].second);
            if (!std::in_range<uint8_t>(count))
                continue;

            synthesis.newItemType = type;
            synthesis.newItemTypeId = typeId;
            synthesis.newItemCount = count;

            if (auto it = g_itemSyntheses.find(itemId); it != g_itemSyntheses.end())
                it->second.push_back(synthesis);
            else
                g_itemSyntheses.insert({ itemId, { synthesis } });
        }

        for (const auto& [itemId, syntheses] : g_itemSyntheses)
        {
            ChaoticSquare chaoticSquare{};
            chaoticSquare.itemId = itemId;

            auto view = std::views::zip(
                chaoticSquare.newItemType,
                chaoticSquare.newItemTypeId
            );

            size_t index = 0;
            for (const auto& synthesis : syntheses)
            {
                std::get<0>(view[index]) = synthesis.newItemType;
                std::get<1>(view[index]) = synthesis.newItemTypeId;

                ++index;

                if (index < view.size())
                    continue;
                else
                {
                    g_chaoticSquares.push_back(chaoticSquare);
                    std::fill(view.begin(), view.end(), std::tuple(0, 0));
                    index = 0;
                }
            }

            if (!index)
                continue;

            g_chaoticSquares.push_back(chaoticSquare);
        }
    }
    catch (...)
    {
        g_itemSyntheses.clear();
        g_chaoticSquares.clear();
    }
}

void Configuration::LoadRewardItemEvent()
{
    try
    {
        std::filesystem::path path(m_root);
        ext::filesystem::combine(path, "Data", "RewardItem.ini");

        if (!std::filesystem::exists(path))
            return;

        auto sections = util::ini::get_sections(path);
        auto dest = g_rewardItemList.begin();

        for (const auto& section : sections)
        {
            auto pairs = util::ini::get_pairs(section.c_str(), path);
            if (pairs.size() != 4)
                continue;

            auto minutes = std::stoi(pairs[0].second);
            if (minutes <= 0)
                continue;

            auto type = std::stoi(pairs[1].second);
            if (!std::in_range<uint8_t>(type))
                continue;

            auto typeId = std::stoi(pairs[2].second);
            if (!std::in_range<uint8_t>(typeId))
                continue;

            auto count = std::stoi(pairs[3].second);
            if (!std::in_range<uint8_t>(count))
                continue;

            dest->minutes = minutes;
            dest->type = type;
            dest->typeId = typeId;
            dest->count = count;

            ++dest;
            ++g_rewardItemCount;

            if (dest == g_rewardItemList.end())
                break;
        }
    }
    catch (...)
    {
        g_rewardItemCount = 0;
        g_rewardItemList.fill({});
    }
}
