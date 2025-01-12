#include <ranges>
#include <string>
#include <strsafe.h>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/Helpers.h"
#include "include/shaiya/include/ItemEnchant.h"
#include "include/shaiya/include/ItemInfo.h"
#include "include/shaiya/include/network/game/incoming/0100.h"
#include "include/shaiya/include/network/game/outgoing/0100.h"
#include "include/shaiya/include/network/game/outgoing/0700.h"
#include "include/shaiya/include/network/dbAgent/incoming/0400.h"
#include "include/shaiya/include/network/dbAgent/outgoing/0400.h"
using namespace shaiya;

namespace packet_character
{
    /// <summary>
    /// Handles incoming 0x119 packets.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void name_available_handler(CUser* user, CharNameAvailableIncoming* incoming)
    {
        incoming->name[incoming->name.size() - 1] = '\0';
        auto nameLength = std::strlen(incoming->name.data());

        if (nameLength < 3 || nameLength > 13)
        {
            CharNameAvailableOutgoing outgoing(false);
            Helpers::Send(user, &outgoing, sizeof(CharNameAvailableOutgoing));
            return;
        }

        DBAgentCharNameAvailableIncoming request(user->userId, incoming->name.data());
        int length = request.size_without_name() + nameLength + 1;
        Helpers::SendDBAgent(&request, length);
    }

    /// <summary>
    /// Sends packet 0x119 to the user.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="response"></param>
    void send_name_available(CUser* user, DBAgentCharNameAvailableOutgoing* response)
    {
        CharNameAvailableOutgoing outgoing(response->available);
        Helpers::Send(user, &outgoing, sizeof(CharNameAvailableOutgoing));
    }

    /// <summary>
    /// Sends packet 0x711 (6.4) to the user. The item dates will be zero.
    /// </summary>
    /// <param name="user"></param>
    void send_warehouse(CUser* user)
    {
        UserBankItemListOutgoing_EP6_4 outgoing{};
        outgoing.bankMoney = user->bankMoney;
        outgoing.itemCount = 0;

        // Please note that warehouse access is read-only
        for (const auto& [slot, item] : std::views::enumerate(
            std::as_const(user->warehouse)))
        {
            if (!item)
                continue;

            Item0711_EP6_4 item0711{};
            item0711.slot = slot;
            item0711.type = item->type;
            item0711.typeId = item->typeId;
            item0711.quality = item->quality;
            item0711.gems = item->gems;
            item0711.count = item->count;
            item0711.craftName = item->craftName;
            outgoing.itemList[outgoing.itemCount] = item0711;

            ++outgoing.itemCount;

            if (outgoing.itemCount < outgoing.itemList.size())
                continue;
            else
            {
                int length = UserBankItemListOutgoing_EP6_4::baseLength + (outgoing.itemCount * sizeof(Item0711_EP6_4));
                Helpers::Send(user, &outgoing, length);

                outgoing.itemCount = 0;
                outgoing.itemList = {};
            }
        }

        if (!outgoing.itemCount)
            return;

        int length = UserBankItemListOutgoing_EP6_4::baseLength + (outgoing.itemCount * sizeof(Item0711_EP6_4));
        Helpers::Send(user, &outgoing, length);
    }

    /// <summary>
    /// Sends packet 0x116 to the user. The client defense step values 
    /// are hard-coded to be multiples of five.
    /// </summary>
    /// <param name="user"></param>
    void send_weapon_step(CUser* user)
    {
        LapisianEnchantWeaponStepOutgoing outgoing{};

        for (int i = 0; std::cmp_less(i, outgoing.addValue.size()); ++i)
            outgoing.addValue[i] = g_LapisianEnchantAddValue->step[i].weapon;

        Helpers::Send(user, &outgoing, sizeof(LapisianEnchantWeaponStepOutgoing));
    }

    /// <summary>
    /// Sends packet 0x101 (6.4) to the user.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="dbCharacter"></param>
    void send_character(CUser* user, Character0403_EP6_4* dbCharacter)
    {
        CharacterOutgoing_EP6_4 character{};
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
        character.equipment = dbCharacter->equipment;
        StringCbCopyA(character.charName.data(), character.charName.size(), dbCharacter->charName.data());
        character.nameChange = dbCharacter->nameChange;
        character.deleted = dbCharacter->deleteDate ? true : false;
        character.cloakBadge = dbCharacter->cloakBadge;
        Helpers::Send(user, &character, sizeof(CharacterOutgoing_EP6_4));
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

unsigned u0x4920F0 = 0x4920F0;
unsigned u0x47BCED = 0x47BCED;
void __declspec(naked) naked_0x47BCE8()
{
    __asm
    {
        call u0x4920F0

        pushad

        push ebp // user
        call packet_character::send_weapon_step
        add esp,0x4

        popad

        jmp u0x47BCED
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
    // CUser::PacketUserDBChar switch
    util::detour((void*)0x47B3E7, naked_0x47B3E7, 5);
    // CUser::PacketUserDBChar case 0x407
    util::detour((void*)0x47BCE8, naked_0x47BCE8, 5);

    // CUser::PacketUserDBChar
    util::write_memory((void*)0x47B4EC, sizeof(Character0403_EP6_4), 1);
    util::write_memory((void*)0x47B9C9, sizeof(Character0403_EP6_4), 1);
}
