#include <algorithm>
#include <chrono>
#include <filesystem>
#include <format>
#include <map>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/network/game/RewardItemUnit.h>
#include "include/extensions/filesystem.hpp"
#include "include/extensions/functional.hpp"
#include "include/extensions/string.hpp"
#include "BattlefieldMoveInfo.h"
#include "ChaoticSquare.h"
#include "ChaoticSquarePredicate.h"
#include "Configuration.h"
#include "Ini.h"
#include "ItemInfo.h"
#include "ResultItem.h"
#include "RewardItem.h"
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

        for (int num = 1; num < count + 1; ++num)
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
        recipeMax = std::clamp(recipeMax, 0, 1000);
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

        for (int num = 1; num < recipeMax + 1; ++num)
        {
            auto key1 = std::format(L"Recipe_{}:Hidden", num);
            auto hidden = ini.GetValueOrDefault(key1, 0);
            auto key2 = std::format(L"Recipe_{}:Chance", num);
            auto chance = ini.GetValueOrDefault(key2, 0);
            auto key3 = std::format(L"Recipe_{}:Result", num);
            auto result = ini.GetValueOrDefault(key3, L"");
            auto vec = ext::string::split(result, L',', 3);
            if (vec.size() != 3)
                continue;

            ChaoticSquareRecipe recipe{};
            recipe.id = num;
            recipe.hidden = std::clamp(hidden, 0, 1);
            recipe.chance = std::clamp(chance, 100, 10000);
            recipe.resultItem.type = std::stoi(vec[0]);
            recipe.resultItem.typeId = std::stoi(vec[1]);
            recipe.resultItem.count = std::stoi(vec[2]);

            for (int i = 0; i < 24; ++i)
            {
                auto key = std::format(L"Recipe_{}:Material_{}", num, i + 1);
                auto value = ini.GetValueOrDefault(key, L"");
                auto vec = ext::string::split(value, L',', 3);
                vec.resize(3, L"0");

                recipe.materialType[i] = std::stoi(vec[0]);
                recipe.materialTypeId[i] = std::stoi(vec[1]);
                recipe.materialCount[i] = std::stoi(vec[2]);
            }

            g_chaoticSquareRecipes.push_back(recipe);
        }

        for (int num = 1; num < squareMax + 1; ++num)
        {
            auto key = std::format(L"Square_{}:ItemCtId", num);
            auto value = ini.GetValueOrDefault(key, L"");
            auto vec = ext::string::split(value, L',', 2);
            if (vec.size() != 2)
                continue;

            auto itemType = std::stoi(vec[0]);
            auto itemTypeId = std::stoi(vec[1]);
            auto itemId = (itemType * 1000) + itemTypeId;

            key = std::format(L"Square_{}:RecipeList", num);
            value = ini.GetValueOrDefault(key, L"");
            vec = ext::string::split(value, L',');
            if (vec.empty())
                continue;

            std::vector<int> recipeList;
            std::transform(vec.cbegin(), vec.cend(), std::back_inserter(recipeList), ext::string::to_int());
            std::sort(recipeList.begin(), recipeList.end());

            ChaoticSquare square{};
            square.itemId = itemId;
            square.recipeList = recipeList;

            auto dest = square.failItems.begin();
            for (int i = 0; i < 24; ++i)
            {
                auto key = std::format(L"Square_{}:Fail_Item_{}", num, i + 1);
                auto value = ini.GetValueOrDefault(key, L"");
                auto vec = ext::string::split(value, L',', 3);
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

            int i = 0;
            for (const auto& id : square.recipeList)
            {
                auto recipe = ChaoticSquare::FindRecipe(id);
                if (!recipe)
                    continue;

                if (recipe->hidden)
                    continue;

                resultList.itemType[i] = recipe->resultItem.type;
                resultList.itemTypeId[i] = recipe->resultItem.typeId;
                ++i;

                if (i < 10)
                    continue;
                else
                {
                    square.resultLists.push_back(resultList);
                    resultList = {};
                    i = 0;
                }
            }

            if (!i)
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
        ext::filesystem::path::combine(path, "Data", "SetItem.ini");
        if (!std::filesystem::exists(path))
            return;

        Ini ini(path);
        ini.Read();

        auto str1 = ini.GetValueOrDefault(L"SetItem_String:MainString", L"");
        auto str2 = ini.GetValueOrDefault(L"SetItem_String:SubString", L"");
        if (str1.empty() || str2.empty())
            return;

        auto itemSetMax = ini.GetValueOrDefault(L"SetItem_Max:SetItem_Max", 0);
        itemSetMax = std::clamp(itemSetMax, 0, 200);
        if (itemSetMax <= 0)
            return;

        auto effectMax = ini.GetValueOrDefault(L"SetItem_Max:Effect_Max", 0);
        effectMax = std::clamp(effectMax, 0, 13);
        if (effectMax <= 0)
            return;

        g_itemSets.reserve(itemSetMax);

        for (int num = 1; num < itemSetMax + 1; ++num)
        {
            ItemSet itemSet{};
            itemSet.id = num;

            for (int i = 0; i < effectMax; ++i)
            {
                auto key1 = std::format(L"{}_{}_{}_{}:HP", str1, num, str2, i + 1);
                auto value1 = ini.GetValueOrDefault(key1, 0);
                auto key2 = std::format(L"{}_{}_{}_{}:MP", str1, num, str2, i + 1);
                auto value2 = ini.GetValueOrDefault(key2, 0);
                auto key3 = std::format(L"{}_{}_{}_{}:SP", str1, num, str2, i + 1);
                auto value3 = ini.GetValueOrDefault(key3, 0);

                auto key4 = std::format(L"{}_{}_{}_{}:STR", str1, num, str2, i + 1);
                auto value4 = ini.GetValueOrDefault(key4, 0);
                auto key5 = std::format(L"{}_{}_{}_{}:DEX", str1, num, str2, i + 1);
                auto value5 = ini.GetValueOrDefault(key5, 0);
                auto key6 = std::format(L"{}_{}_{}_{}:REC", str1, num, str2, i + 1);
                auto value6 = ini.GetValueOrDefault(key6, 0);
                auto key7 = std::format(L"{}_{}_{}_{}:INT", str1, num, str2, i + 1);
                auto value7 = ini.GetValueOrDefault(key7, 0);
                auto key8 = std::format(L"{}_{}_{}_{}:WIS", str1, num, str2, i + 1);
                auto value8 = ini.GetValueOrDefault(key8, 0);
                auto key9 = std::format(L"{}_{}_{}_{}:LUC", str1, num, str2, i + 1);
                auto value9 = ini.GetValueOrDefault(key9, 0);

                auto key10 = std::format(L"{}_{}_{}_{}:AtkFL", str1, num, str2, i + 1);
                auto value10 = ini.GetValueOrDefault(key10, 0);
                auto key11 = std::format(L"{}_{}_{}_{}:AtkSH", str1, num, str2, i + 1);
                auto value11 = ini.GetValueOrDefault(key11, 0);
                auto key12 = std::format(L"{}_{}_{}_{}:AtkMG", str1, num, str2, i + 1);
                auto value12 = ini.GetValueOrDefault(key12, 0);

                auto key13 = std::format(L"{}_{}_{}_{}:DefFL", str1, num, str2, i + 1);
                auto value13 = ini.GetValueOrDefault(key13, 0);
                auto key14 = std::format(L"{}_{}_{}_{}:DefSH", str1, num, str2, i + 1);
                auto value14 = ini.GetValueOrDefault(key14, 0);
                auto key15 = std::format(L"{}_{}_{}_{}:DefMG", str1, num, str2, i + 1);
                auto value15 = ini.GetValueOrDefault(key15, 0);

                // STR, DEX, REC, INT, WIS, LUC
                itemSet.synergies[i].effects[0] = value4;
                itemSet.synergies[i].effects[1] = value5;
                itemSet.synergies[i].effects[2] = value6;
                itemSet.synergies[i].effects[3] = value7;
                itemSet.synergies[i].effects[4] = value8;
                itemSet.synergies[i].effects[5] = value9;
                // HP, MP, SP
                itemSet.synergies[i].effects[6] = value1;
                itemSet.synergies[i].effects[7] = value2;
                itemSet.synergies[i].effects[8] = value3;
                // Attack
                itemSet.synergies[i].effects[9] = value10;
                itemSet.synergies[i].effects[10] = value11;
                itemSet.synergies[i].effects[11] = value12;
                // Defense
                itemSet.synergies[i].effects[12] = value13;
                itemSet.synergies[i].effects[13] = value14;
                itemSet.synergies[i].effects[14] = value15;
            }

            g_itemSets.push_back(itemSet);
        }
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

        for (int i = 0; i < count; ++i)
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
