#include <filesystem>
#include <format>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <extensions/include/string.hpp>
#include "BattlefieldMoveInfo.h"
#include "Configuration.h"
#include "Ini.h"
#include "SAFile.h"
#include "Static.h"
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
        auto handle = SAFile::Open("data/BattleFieldMoveInfo_Client.ini", "rb");
        if (!handle)
            return;

        // to-do: figure out the code for the else block

        auto file = g_var->file;
        if (!file)
        {
            SAFile::Close(handle);
            return;
        }

        std::string buffer(file->length, 0);
        SAFile::Read(buffer.data(), 1, buffer.size(), handle);
        SAFile::Close(handle);

        auto ini = Ini::Parse(ext::string::to_wstring(buffer));
        auto count = ini.GetValueOrDefault(L"BATTLEFIELD_INFO:BATTLEFIELD_COUNT", 0);
        if (count <= 0)
            return;

        g_pvpMoveData.reserve(count);

        for (int num = 1; num < count + 1; ++num)
        {
            auto key1 = std::format(L"BATTLEFIELD_{}:MAP_NO", num);
            auto mapId = ini.GetValueOrDefault(key1, -1);
            if (mapId == -1)
                continue;

            auto key2 = std::format(L"BATTLEFIELD_{}:LEVEL_MIN", num);
            auto levelMin = ini.GetValueOrDefault(key2, 0);
            auto key3 = std::format(L"BATTLEFIELD_{}:LEVEL_MAX", num);
            auto levelMax = ini.GetValueOrDefault(key3, 0);

            BattlefieldMoveInfo info{};
            info.mapId = mapId;
            info.levelMin = levelMin;
            info.levelMax = levelMax;
            g_pvpMoveData.push_back(info);
        }
    }
    catch (...)
    {
        g_pvpMoveData.clear();
    }
}
