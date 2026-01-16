#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <format>
#include <map>
#include <ranges>
#include <string>
#include <tuple>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/network/game/RewardItemUnit.h>
#include "include/extensions/filesystem.hpp"
#include "include/extensions/functional.hpp"
#include "include/extensions/ranges.hpp"
#include "BattlefieldMoveInfo.h"
#include "ChaoticSquare.h"
#include "ChaoticSquarePredicate.h"
#include "Configuration.h"
#include "Ini.h"
#include "ItemInfo.h"
#include "ResultItem.h"
#include "RewardItem.h"
#include "SBinaryReader.h"
#include "Synergy.h"
using namespace shaiya;

void Configuration::Init()
{
    std::wstring output(INT16_MAX, 0);
    auto count = GetModuleFileNameW(nullptr, output.data(), INT16_MAX);
    if (!count)
        return;

    auto first = output.begin();
    auto last = first + count;
    m_root.assign(first, last).remove_filename();
}

void Configuration::LoadBattlefieldMoveData()
{
    try
    {
        std::filesystem::path path(m_root);
        ext::filesystem::path::combine(path, "Data", "BattleFieldMoveInfo.ini");
        if (!std::filesystem::exists(path))
            return;

        Ini ini(path);
        ini.Read();

        auto count = ini.GetValueOrDefault(L"BATTLEFIELD_INFO:BATTLEFIELD_COUNT", 0);
        if (count <= 0)
            return;

        for (auto num : std::views::iota(1, count + 1))
        {
            auto key1 = std::format(L"BATTLEFIELD_{}:MAP_NO", num);
            auto mapId = ini.GetValueOrDefault(key1, 0);
            auto key2 = std::format(L"BATTLEFIELD_{}:LEVEL_MIN", num);
            auto levelMin = ini.GetValueOrDefault(key2, 0);
            auto key3 = std::format(L"BATTLEFIELD_{}:LEVEL_MAX", num);
            auto levelMax = ini.GetValueOrDefault(key3, 0);

            BattlefieldMoveInfo info{};
            info.levelMin = levelMin;
            info.levelMax = levelMax;

            auto keyX = std::format(L"BATTLEFIELD_{}:HU_POSX", num);
            auto x = ini.GetValueOrDefault(keyX, L"");
            auto keyY = std::format(L"BATTLEFIELD_{}:HU_POSY", num);
            auto y = ini.GetValueOrDefault(keyY, L"");
            auto keyZ = std::format(L"BATTLEFIELD_{}:HU_POSZ", num);
            auto z = ini.GetValueOrDefault(keyZ, L"");

            info.mapPos[0].mapId = mapId;
            info.mapPos[0].x = std::stof(x);
            info.mapPos[0].y = std::stof(y);
            info.mapPos[0].z = std::stof(z);

            keyX = std::format(L"BATTLEFIELD_{}:EL_POSX", num);
            x = ini.GetValueOrDefault(keyX, L"");
            keyY = std::format(L"BATTLEFIELD_{}:EL_POSY", num);
            y = ini.GetValueOrDefault(keyY, L"");
            keyZ = std::format(L"BATTLEFIELD_{}:EL_POSZ", num);
            z = ini.GetValueOrDefault(keyZ, L"");

            info.mapPos[1].mapId = mapId;
            info.mapPos[1].x = std::stof(x);
            info.mapPos[1].y = std::stof(y);
            info.mapPos[1].z = std::stof(z);

            keyX = std::format(L"BATTLEFIELD_{}:VI_POSX", num);
            x = ini.GetValueOrDefault(keyX, L"");
            keyY = std::format(L"BATTLEFIELD_{}:VI_POSY", num);
            y = ini.GetValueOrDefault(keyY, L"");
            keyZ = std::format(L"BATTLEFIELD_{}:VI_POSZ", num);
            z = ini.GetValueOrDefault(keyZ, L"");

            info.mapPos[3].mapId = mapId;
            info.mapPos[3].x = std::stof(x);
            info.mapPos[3].y = std::stof(y);
            info.mapPos[3].z = std::stof(z);

            keyX = std::format(L"BATTLEFIELD_{}:DE_POSX", num);
            x = ini.GetValueOrDefault(keyX, L"");
            keyY = std::format(L"BATTLEFIELD_{}:DE_POSY", num);
            y = ini.GetValueOrDefault(keyY, L"");
            keyZ = std::format(L"BATTLEFIELD_{}:DE_POSZ", num);
            z = ini.GetValueOrDefault(keyZ, L"");

            info.mapPos[2].mapId = mapId;
            info.mapPos[2].x = std::stof(x);
            info.mapPos[2].y = std::stof(y);
            info.mapPos[2].z = std::stof(z);

            // Not implemented
            //auto key4 = std::format(L"BATTLEFIELD_{}:MOVE_SPOT_RANGE", num);
            //auto range = ini.GetValueOrDefault(key4, 0);

            if (!g_pvpZones.contains(mapId))
                g_pvpZones[mapId] = info;
        }
    }
    catch (...)
    {
        g_pvpZones.clear();
    }
}

void Configuration::LoadChaoticSquareData()
{
    try
    {
        std::filesystem::path path(m_root);
        ext::filesystem::path::combine(path, "Data", "ChaoticSquare.ini");
        if (!std::filesystem::exists(path))
            return;

        Ini ini(path);
        ini.Read();

        auto recipeMax = ini.GetValueOrDefault(L"Info:RecipeMax", 0);
        if (recipeMax <= 0)
            return;

        auto squareMax = ini.GetValueOrDefault(L"Info:SquareMax", 0);
        if (squareMax <= 0)
            return;

        auto money = ini.GetValueOrDefault(L"Info:FortuneMoney", 100'000'000);
        if (money <= 0)
            return;

        g_chaoticSquareFortuneMoney = money;
        g_chaoticSquareRecipes.reserve(recipeMax);
        g_chaoticSquares.reserve(squareMax);

        for (auto num : std::views::iota(1, recipeMax + 1))
        {
            auto key1 = std::format(L"Recipe_{}:Hidden", num);
            auto hidden = ini.GetValueOrDefault(key1, 0);
            auto key2 = std::format(L"Recipe_{}:Chance", num);
            auto chance = ini.GetValueOrDefault(key2, 0);
            auto key3 = std::format(L"Recipe_{}:Result", num);
            auto result = ini.GetValueOrDefault(key3, L"");
            auto vec = ext::views::split_to<std::vector<std::wstring>>(result, L',', 3);
            if (vec.size() != 3)
                continue;

            ChaoticSquareRecipe recipe{};
            recipe.id = num;
            recipe.hidden = std::clamp(hidden, 0, 1);
            recipe.chance = std::clamp(chance, 100, 10000);
            recipe.resultItem.type = std::stoi(vec[0]);
            recipe.resultItem.typeId = std::stoi(vec[1]);
            recipe.resultItem.count = std::stoi(vec[2]);

            auto view = std::views::zip(
                recipe.materialType, 
                recipe.materialTypeId, 
                recipe.materialCount);

            for (auto i : std::views::iota(0, std::ssize(view)))
            {
                auto key = std::format(L"Recipe_{}:Material_{}", num, i + 1);
                auto value = ini.GetValueOrDefault(key, L"");
                auto vec = ext::views::split_to<std::vector<std::wstring>>(value, L',', 3);
                vec.resize(3, L"0");

                std::get<0>(view[i]) = std::stoi(vec[0]);
                std::get<1>(view[i]) = std::stoi(vec[1]);
                std::get<2>(view[i]) = std::stoi(vec[2]);
            }

            g_chaoticSquareRecipes.push_back(recipe);
        }

        for (auto num : std::views::iota(1, squareMax + 1))
        {
            auto key = std::format(L"Square_{}:ItemCtId", num);
            auto value = ini.GetValueOrDefault(key, L"");
            auto vec = ext::views::split_to<std::vector<std::wstring>>(value, L',', 2);
            if (vec.size() != 2)
                continue;

            auto itemType = std::stoi(vec[0]);
            auto itemTypeId = std::stoi(vec[1]);
            auto itemId = (itemType * 1000) + itemTypeId;

            key = std::format(L"Square_{}:RecipeList", num);
            value = ini.GetValueOrDefault(key, L"");
            vec = ext::views::split_to<std::vector<std::wstring>>(value, L',');
            if (vec.empty())
                continue;

            std::vector<int> recipeList;
            std::transform(vec.cbegin(), vec.cend(), std::back_inserter(recipeList), ext::string_to_int());
            std::sort(recipeList.begin(), recipeList.end());

            ChaoticSquare square{};
            square.itemId = itemId;
            square.recipeList = recipeList;

            auto dest = square.failItems.begin();
            for (auto i : std::views::iota(1, std::ssize(square.failItems) + 1))
            {
                auto key = std::format(L"Square_{}:Fail_Item_{}", num, i);
                auto value = ini.GetValueOrDefault(key, L"");
                auto vec = ext::views::split_to<std::vector<std::wstring>>(value, L',', 3);
                vec.resize(3, L"0");

                dest->type = std::stoi(vec[0]);
                dest->typeId = std::stoi(vec[1]);
                dest->count = std::stoi(vec[2]);
                ++dest;
            }

            g_chaoticSquares.push_back(square);
        }

        for (auto&& square : g_chaoticSquares)
        {
            ChaoticSquareResultList resultList{};
            
            auto view = std::views::zip(
                resultList.itemType,
                resultList.itemTypeId);
 
            auto index = 0;
            for (const auto& id : square.recipeList)
            {
                auto recipe = ChaoticSquare::FindRecipe(id);
                if (!recipe)
                    continue;

                if (recipe->hidden)
                    continue;

                std::get<0>(view[index]) = recipe->resultItem.type;
                std::get<1>(view[index]) = recipe->resultItem.typeId;
                ++index;

                if (index < std::ssize(view))
                    continue;
                else
                {
                    square.resultLists.push_back(resultList);
                    std::fill(view.begin(), view.end(), std::tuple(0, 0));
                    index = 0;
                }
            }

            if (!index)
                continue;

            square.resultLists.push_back(resultList);
        }
    }
    catch (...)
    {
        g_chaoticSquareRecipes.clear();
        g_chaoticSquares.clear();
    }
}

void Configuration::LoadItemSetData()
{
    try
    {
        std::filesystem::path path(m_root);
        ext::filesystem::path::combine(path, "Data", "SetItem.SData");
        if (!std::filesystem::exists(path))
            return;

        SBinaryReader reader(path);
        auto itemSetCount = reader.readUInt32();
        g_itemSets.resize(itemSetCount);

        for (auto&& itemSet : g_itemSets)
        {
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
                // e.g., 70,50,0,0,0,20,0,0,0,0,0,0,0,0,0
                auto input = reader.readString();
                if (input.starts_with('\0'))
                    continue;

                auto count = synergy.effects.size();
                auto vec = ext::views::split_to<std::vector<std::string>>(input, ',', count);
                vec.resize(count, "0");

                auto dest = synergy.effects.begin();
                std::transform(vec.cbegin(), vec.cend(), dest, ext::string_to_int());
            }
        }

        reader.close();
    }
    catch (...)
    {
        g_itemSets.clear();
    }
}

void Configuration::LoadOnlineTimePrizeData()
{
    try
    {
        std::filesystem::path path(m_root);
        ext::filesystem::path::combine(path, "Data", "OnlineTimePrize.ini");
        if (!std::filesystem::exists(path))
            return;

        Ini ini(path);
        ini.Read();

        auto count = ini.GetValueOrDefault(L"OnlineTimePrize:Count", 0);
        count = std::clamp(count, 0, 20);
        if (!count)
            return;

        auto dest = g_rewardItemList.begin();
        g_rewardItemCount = 0;

        for (auto i : std::views::iota(0, count))
        {
            auto key1 = std::format(L"OnlineTimePrize{:02d}:ItemID", i);
            auto itemId = ini.GetValueOrDefault(key1, 0);
            if (itemId <= 0)
                continue;

            auto key2 = std::format(L"OnlineTimePrize{:02d}:ItemCount", i);
            auto itemCount = ini.GetValueOrDefault(key2, 0);
            if (itemCount <= 0)
                continue;

            auto key3 = std::format(L"OnlineTimePrize{:02d}:NeedTime", i);
            auto needTime = ini.GetValueOrDefault(key3, 0);
            if (needTime <= 0)
                continue;

            // e.g., 1800s -> 30min
            auto seconds = std::chrono::seconds(needTime);
            auto minutes = std::chrono::duration_cast<std::chrono::minutes>(seconds);
            dest->minutes = minutes.count();
            // e.g., 100001
            auto itemType = itemId / 1000;   // 100
            auto itemTypeId = itemId % 1000; // 1
            dest->type = itemType;
            dest->typeId = itemTypeId;
            dest->count = itemCount;

            ++dest;
            ++g_rewardItemCount;
        }
    }
    catch (...)
    {
        g_rewardItemCount = 0;
        g_rewardItemList.fill({});
    }
}
