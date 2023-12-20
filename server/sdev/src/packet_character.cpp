#include <string>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <strsafe.h>

#include <include/main.h>
#include <include/util.h>
#include <include/shaiya/packets/0100.h>
#include <include/shaiya/packets/0700.h>
#include <include/shaiya/packets/dbAgent/0400.h>
#include <include/shaiya/include/CItem.h>
#include <include/shaiya/include/CUser.h>
#include <include/shaiya/include/SConnection.h>
#include <include/shaiya/include/SConnectionTBaseReconnect.h>
#include <include/shaiya/include/ServerTime.h>
using namespace shaiya;

namespace packet_character
{
    void name_available_handler(CUser* user, const char* name)
    {
        constexpr int packet_size_without_name = 6;

        UserCharNameAvailableIncoming request{};
        request.userId = user->userId;

        std::string charName(name);
        if (charName.length() < 3 || charName.length() > 13)
        {
            CharNameAvailableOutgoing packet{ 0x119, false };
            SConnection::Send(&user->connection, &packet, sizeof(CharNameAvailableOutgoing));
            return;
        }

        StringCbCopyA(request.charName.data(), request.charName.size(), charName.data());

        int length = packet_size_without_name + charName.length() + 1;
        SConnectionTBaseReconnect::Send(g_pClientToDBAgent, &request, length);
    }

    void send_name_available(CUser* user, Packet buffer)
    {
        auto available = util::read_bytes<bool>(buffer, 6);
        CharNameAvailableOutgoing packet{ 0x119, available };
        SConnection::Send(&user->connection, &packet, sizeof(CharNameAvailableOutgoing));
    }

    void send_warehouse(CUser* user)
    {
        constexpr int packet_size_without_list = 7;
        constexpr int max_item_list_count = 40;

        UserBankItemListOutgoing warehouse{};
        warehouse.bankMoney = user->bankMoney;
        warehouse.itemCount = 0;

        for (int slot = 0; slot < max_warehouse_slot; ++slot)
        {
            auto& item = user->warehouse[slot];
            if (!item)
                continue;

            Item0711 item0711{};
            item0711.slot = slot;
            item0711.type = item->type;
            item0711.typeId = item->typeId;
            item0711.quality = item->quality;
            item0711.gems = item->gems;
            item0711.count = item->count;

            #ifdef SHAIYA_EP6_ITEM_DURATION
            if (ServerTime::IsTimedItem(item->itemInfo))
            {
                item0711.toDate = ServerTime::GetExpireTime(item->makeTime, item->itemInfo->range);
                item0711.fromDate = item0711.toDate ? item->makeTime : 0;
            }
            #endif

            item0711.craftName = item->craftName;
            warehouse.itemList[warehouse.itemCount] = item0711;

            ++warehouse.itemCount;

            if (warehouse.itemCount != max_item_list_count)
                continue;
            else
            {
                int length = packet_size_without_list + (warehouse.itemCount * sizeof(Item0711));
                SConnection::Send(&user->connection, &warehouse, length);

                std::memset(&warehouse.itemList, 0, sizeof(warehouse.itemList));
                warehouse.itemCount = 0;
            }
        }

        if (warehouse.itemCount <= 0)
            return;

        int length = packet_size_without_list + (warehouse.itemCount * sizeof(Item0711));
        SConnection::Send(&user->connection, &warehouse, length);
    }

    void send_character(CUser* user, Character0403* dbCharacter)
    {
        CharacterOutgoing character{};
        character.slot = dbCharacter->slot;
        character.charId = dbCharacter->id;
        character.regDate = dbCharacter->regDate;
        character.level = dbCharacter->level;
        character.family = dbCharacter->family;
        character.grow = dbCharacter->grow;
        character.hair = dbCharacter->hair;
        character.face = dbCharacter->face;
        character.size = dbCharacter->size;
        character.job = dbCharacter->job;
        character.sex = dbCharacter->sex;
        character.mapId = dbCharacter->mapId;
        character.strength = dbCharacter->strength;
        character.dexterity = dbCharacter->dexterity;
        character.reaction = dbCharacter->reaction;
        character.intelligence = dbCharacter->intelligence;
        character.wisdom = dbCharacter->wisdom;
        character.luck = dbCharacter->luck;
        character.health = dbCharacter->health;
        character.mana = dbCharacter->mana;
        character.stamina = dbCharacter->stamina;
        std::memcpy(&character.equipment, &dbCharacter->equipment, sizeof(Equipment0403));
        StringCbCopyA(character.charName.data(), character.charName.size(), dbCharacter->charName.data());
        character.deleted = dbCharacter->deleted;
        character.nameChange = dbCharacter->nameChange;
        character.cloakBadge = dbCharacter->cloakBadge;
        SConnection::Send(&user->connection, &character, sizeof(CharacterOutgoing));
    }
}

unsigned u0x47A237 = 0x47A237;
unsigned u0x47A574 = 0x47A574;
void __declspec(naked) naked_0x47A231()
{
    __asm
    {
        // original
        add eax,-0x102
        push ebx

        cmp eax,0x17
        je case_0x119
        jmp u0x47A237

        case_0x119:
        pushad

        lea eax,[edi+0x2]
        push eax // name
        push esi // user
        call packet_character::name_available_handler
        add esp,0x8

        popad

        jmp u0x47A574
    }
}

void __declspec(naked) naked_0x492660()
{
    __asm
    {
        pushad

        push ebp // user
        call packet_character::send_warehouse
        add esp,0x4

        popad
        
        retn 0x4
    }
}

unsigned u0x47B9B8 = 0x47B9B8;
void __declspec(naked) naked_0x47B8FB()
{
    __asm
    {
        pushad
        
        push esi // packet
        push ebp // user
        call packet_character::send_character
        add esp,0x8

        popad

        jmp u0x47B9B8
    }
}

unsigned u0x47B3EC = 0x47B3EC;
unsigned u0x47BDCC = 0x47BDCC;
void __declspec(naked) naked_0x47B3E7()
{
    __asm
    {
        // original
        add eax,-0x401
        cmp eax,0xC
        je case_0x40D
        jmp u0x47B3EC

        case_0x40D:
        pushad

        push edi // packet
        push ebp // user
        call packet_character::send_name_available
        add esp,0x8

        popad

        mov al,0x1
        jmp u0x47BDCC
    }
}

void hook::packet_character()
{
    // CUser::PacketCharacter switch
    util::detour((void*)0x47A231, naked_0x47A231, 6);
    // CUser::SendCharacterBank
    util::detour((void*)0x492660, naked_0x492660, 6);
    // CUser::PacketUserDBChar case 0x403
    util::detour((void*)0x47B8FB, naked_0x47B8FB, 6);
    // CUser::PacketUserDBChar
    util::detour((void*)0x47B3E7, naked_0x47B3E7, 5);

    // CUser::PacketUserDBChar
    util::write_memory((void*)0x47B4EC, sizeof(Character0403), 1);
    util::write_memory((void*)0x47B9C9, sizeof(Character0403), 1);
}
