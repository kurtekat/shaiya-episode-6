#include <filesystem>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <ini/ini.h>
#include "include/shaiya/include/ItemRemake.h"
using namespace ini;
using namespace shaiya;

void ItemRemake::init()
{
    try
    {
        std::wstring buffer(INT16_MAX, 0);
        if (!GetModuleFileNameW(nullptr, buffer.data(), INT16_MAX))
            return;

        std::filesystem::path path(buffer);
        path.remove_filename();
        path.append("Data");
        path.append("ItemRemake.ini");

        auto sectionNames = IniHelper::getSectionNamesW(path);
        for (const auto& sectionName : sectionNames)
        {
            auto kvp = IniHelper::getSectionW(sectionName, path);
            if (kvp.size() != 5)
                continue;

            ItemRemake remake{};
            remake.itemId1 = std::stoi(kvp[0].second);
            remake.itemId2 = std::stoi(kvp[1].second);
            remake.itemId3 = std::stoi(kvp[2].second);
            remake.createType = std::stoi(kvp[3].second);
            remake.createTypeId = std::stoi(kvp[4].second);
            g_itemRemake.push_back(remake);
        }
    }
    catch (...)
    {
        g_itemRemake.clear();
    }
}
