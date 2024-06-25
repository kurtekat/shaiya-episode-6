#include <ranges>
#include <string>
#include <strsafe.h>
#include <shaiya/include/common/SConnection.h>
#include <shaiya/include/network/dbAgent/incoming/0400.h>
#include <shaiya/include/network/dbAgent/outgoing/0400.h>
#include <shaiya/include/network/game/incoming/0100.h>
#include <shaiya/include/network/game/outgoing/0100.h>
#include <shaiya/include/network/game/outgoing/0700.h>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/Helpers.h"
#include "include/shaiya/include/ItemDuration.h"
#include "include/shaiya/include/ItemInfo.h"
#include "include/shaiya/include/ServerTime.h"
using namespace shaiya;

namespace packet_character
{
    void name_available_handler(CUser* user, CharNameAvailableIncoming* incoming)
    {
        incoming->name[incoming->name.size() - 1] = '\0';
        auto nameLength = std::strlen(incoming->name.data());

        if (nameLength < 3 || nameLength > 13)
        {
            CharNameAvailableOutgoing outgoing(false);
            SConnection::Send(&user->connection, &outgoing, sizeof(CharNameAvailableOutgoing));
            return;
        }

        DBAgentCharNameAvailableIncoming request(user->userId, incoming->name.data());
        int length = request.size_without_name() + nameLength + 1;
        Helpers::SendDBAgent(&request, length);
    }

    void send_name_available(CUser* user, DBAgentCharNameAvailableOutgoing* response)
    {
        CharNameAvailableOutgoing outgoing(response->available);
        SConnection::Send(&user->connection, &outgoing, sizeof(CharNameAvailableOutgoing));
    }

    void send_warehouse(CUser* user)
    {
        UserBankItemListOutgoing outgoing{};
        outgoing.bankMoney = user->bankMoney;
        outgoing.itemCount = 0;

        for (const auto& [slot, item] : std::views::enumerate(
            std::as_const(user->warehouse)))
        {
            if (!item)
                continue;

            Item0711 item0711{};
            item0711.slot = slot;
            item0711.type = item->type;
            item0711.typeId = item->typeId;
            item0711.quality = item->quality;
            item0711.gems = item->gems;
            item0711.count = item->count;

#ifdef SHAIYA_EP6_4_PT
            if (item->itemInfo->duration)
            {
                item0711.fromDate = item->makeTime;
                item0711.toDate = ServerTime::add(item->makeTime, item->itemInfo->duration);
            }
#endif

            item0711.craftName = item->craftName;
            outgoing.itemList[outgoing.itemCount] = item0711;

            ++outgoing.itemCount;

            if (outgoing.itemCount < outgoing.itemList.size())
                continue;
            else
            {
                int length = outgoing.size_without_list() + (outgoing.itemCount * sizeof(Item0711));
                SConnection::Send(&user->connection, &outgoing, length);

                std::memset(&outgoing.itemList, 0, sizeof(outgoing.itemList));
                outgoing.itemCount = 0;
            }
        }

        if (!outgoing.itemCount)
            return;

        int length = outgoing.size_without_list() + (outgoing.itemCount * sizeof(Item0711));
        SConnection::Send(&user->connection, &outgoing, length);
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
        std::copy_n(dbCharacter->equipment.type.begin(), character.equipment.type.size(), character.equipment.type.begin());
        std::copy_n(dbCharacter->equipment.typeId.begin(), character.equipment.typeId.size(), character.equipment.typeId.begin());
        StringCbCopyA(character.charName.data(), character.charName.size(), dbCharacter->charName.data());
        character.nameChange = dbCharacter->nameChange;
        character.deleted = dbCharacter->deleteDate ? true : false;
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

        push edi // packet
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
