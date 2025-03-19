#include <filesystem>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <ini/ini.h>
#include "include/shaiya/include/ItemRemake.h"
using namespace shaiya;

void ItemRemake4::init()
{
    try
    {
        std::wstring buffer(INT16_MAX, 0);
        if (!GetModuleFileNameW(nullptr, buffer.data(), INT16_MAX))
            return;

        std::filesystem::path path(buffer);
        path.remove_filename();
        path.append("Data");
        path.append("ItemRemake4.ini");

        auto sectionNames = ini::IniHelper::getSectionNames(path);
        for (const auto& sectionName : sectionNames)
        {
            auto kvp = ini::IniHelper::getSection(sectionName, path);
            if (kvp.size() != 5)
                continue;

            ItemRemake remake{};
            remake.itemId1 = std::stoi(kvp[0].second);
            remake.itemId2 = std::stoi(kvp[1].second);
            remake.itemId3 = std::stoi(kvp[2].second);
            remake.createType = std::stoi(kvp[3].second);
            remake.createTypeId = std::stoi(kvp[4].second);
            g_itemRemake4.push_back(remake);
        }
    }
    catch (...)
    {
        g_itemRemake4.clear();
    }
}

void ItemRemake5::init()
{
    try
    {
        std::wstring buffer(INT16_MAX, 0);
        if (!GetModuleFileNameW(nullptr, buffer.data(), INT16_MAX))
            return;

        std::filesystem::path path(buffer);
        path.remove_filename();
        path.append("Data");
        path.append("ItemRemake5.ini");

        auto sectionNames = ini::IniHelper::getSectionNames(path);
        for (const auto& sectionName : sectionNames)
        {
            auto kvp = ini::IniHelper::getSection(sectionName, path);
            if (kvp.size() != 5)
                continue;

            ItemRemake remake{};
            remake.itemId1 = std::stoi(kvp[0].second);
            remake.itemId2 = std::stoi(kvp[1].second);
            remake.itemId3 = std::stoi(kvp[2].second);
            remake.createType = std::stoi(kvp[3].second);
            remake.createTypeId = std::stoi(kvp[4].second);
            g_itemRemake5.push_back(remake);
        }
    }
    catch (...)
    {
        g_itemRemake5.clear();
    }
}
