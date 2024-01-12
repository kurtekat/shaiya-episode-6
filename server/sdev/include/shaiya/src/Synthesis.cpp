#include <filesystem>
#include <format>
#include <string>
#include <sstream>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/util.h>
#include <include/shaiya/packets/0200.h>
#include <include/shaiya/packets/dbAgent/0700.h>
#include <include/shaiya/packets/gameLog/0400.h>
#include <include/shaiya/include/CGameData.h>
#include <include/shaiya/include/CItem.h>
#include <include/shaiya/include/CObjectMgr.h>
#include <include/shaiya/include/CUser.h>
#include <include/shaiya/include/Ini.h>
#include <include/shaiya/include/SConnection.h>
#include <include/shaiya/include/SConnectionTBaseReconnect.h>
#include <include/shaiya/include/Synthesis.h>
using namespace shaiya;

void Synthesis::init()
{
    std::vector<char> vec(MAX_PATH);
    GetModuleFileNameA(nullptr, vec.data(), vec.size());

    std::filesystem::path path(vec.data());
    path.remove_filename();
    path.append("Data/ItemSynthesis.ini");

    if (!std::filesystem::exists(path))
    {
        util::log("Synthesis::init file not found");
        return;
    }

    Ini ini(path);

    std::vector<std::string> sections;
    ini.getSectionNames(sections);

    for (const auto& section : sections)
    {
        std::vector<Ini::KeyValPair> vec;
        ini.getSection(section, vec);

        if (vec.size() != 8)
            continue;

        auto itemId = std::strtoul(vec[0].value.c_str(), nullptr, 10);
        int successRate = std::atoi(vec[1].value.c_str());
        successRate = (successRate > 100) ? 100 : successRate;

        Synthesis synthesis{};
        synthesis.successRate = successRate * 100;

        Synthesis::parseMaterial(vec[2].value, synthesis.materialType);
        Synthesis::parseMaterial(vec[3].value, synthesis.materialTypeId);
        Synthesis::parseMaterial(vec[4].value, synthesis.materialCount);

        synthesis.createType = std::atoi(vec[5].value.c_str());
        synthesis.createTypeId = std::atoi(vec[6].value.c_str());
        synthesis.createCount = std::atoi(vec[7].value.c_str());

        auto it = g_synthesis.find(itemId);
        if (it != g_synthesis.end())
            it->second.push_back(synthesis);
        else
            g_synthesis.insert({ itemId, { synthesis } });
    }
}

void Synthesis::parseMaterial(const std::string& text, std::array<std::uint8_t, 24>& output)
{
    if (text.empty())
        return;

    std::istringstream iss(text);
    std::vector<int> vec{};
    for (std::string str; std::getline(iss, str, ','); )
        vec.push_back(std::atoi(str.c_str()));

    if (vec.size() != output.size())
        return;

    std::copy(vec.begin(), vec.end(), output.begin());
}

bool Synthesis::useMaterial(CUser* user, std::uint8_t type, std::uint8_t typeId, std::uint8_t count)
{
    auto itemId = (type * 1000) + typeId;

    for (std::uint8_t bag = 1; bag < max_inventory_bag; ++bag)
    {
        for (std::uint8_t slot = 0; slot < max_inventory_slot; ++slot)
        {
            auto& item = user->inventory[bag][slot];
            if (!item)
                continue;

            if (item->itemInfo->itemId != itemId || item->count < count)
                continue;

            item->count -= count;

            UserItemRemoveIncoming packet{ 0x702, user->userId, bag, slot, count };
            SConnectionTBaseReconnect::Send(g_pClientToDBAgent, &packet, sizeof(UserItemRemoveIncoming));

            GameLogItemRemoveIncoming log{};
            CUser::SetGameLogMain(user, &log);

            log.itemUid = item->uniqueId;
            log.itemId = item->itemInfo->itemId;
            log.itemName = item->itemInfo->itemName;
            log.gems = item->gems;
            log.makeTime = item->makeTime;
            log.craftName = item->craftName;
            log.bag = bag;
            log.slot = slot;
            log.count = count;
            SConnectionTBaseReconnect::Send(g_pClientToGameLog, &log, sizeof(GameLogItemRemoveIncoming));

            if (!item->count)
            {
                ItemRemoveOutgoing outgoing{ 0x206, bag, slot, 0, 0, 0 };
                SConnection::Send(&user->connection, &outgoing, sizeof(ItemRemoveOutgoing));

                CObjectMgr::FreeItem(item);
                user->inventory[bag][slot] = nullptr;
            }
            else
            {
                ItemRemoveOutgoing outgoing{ 0x206, bag, slot, item->type, item->typeId, item->count };
                SConnection::Send(&user->connection, &outgoing, sizeof(ItemRemoveOutgoing));
            }

            return true;
        }
    }

    return false;
}
