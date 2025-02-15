#include <array>
#include <filesystem>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <util/util.h>
#include "include/shaiya/include/IniHelper.h"
#include "include/shaiya/include/ItemRemake.h"
using namespace shaiya;

void ItemRemake::init()
{
    try
    {
        std::array<char, MAX_PATH> fileName{};
        GetModuleFileNameA(nullptr, fileName.data(), fileName.size());

        std::filesystem::path path(fileName.data());
        path.remove_filename();
        path.append("Data");
        path.append("ItemRemake.ini");

        auto sectionNames = IniHelper::getSectionNamesA(path);
        for (const auto& sectionName : sectionNames)
        {
            auto kvp = IniHelper::getSectionA(sectionName, path);
            if (kvp.size() != 5)
                continue;

            ItemRemake remake{};
            remake.itemId1 = util::atoi(kvp[0].second);
            remake.itemId2 = util::atoi(kvp[1].second);
            remake.itemId3 = util::atoi(kvp[2].second);
            remake.createType = util::atoi(kvp[3].second);
            remake.createTypeId = util::atoi(kvp[4].second);
            g_itemRemake.push_back(remake);
        }
    }
    catch (...)
    {
        g_itemRemake.clear();
    }
}
