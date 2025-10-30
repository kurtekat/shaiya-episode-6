#include <filesystem>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <util/ini/ini.h>
#include "ItemRemake.h"
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
