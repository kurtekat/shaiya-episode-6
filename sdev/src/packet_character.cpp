#include <ranges>
#include <string>
#include <util/util.h>
#include <shaiya/include/network/dbAgent/incoming/0400.h>
#include <shaiya/include/network/dbAgent/outgoing/0400.h>
#include <shaiya/include/network/game/incoming/0100.h>
#include <shaiya/include/network/game/outgoing/0100.h>
#include <shaiya/include/network/game/outgoing/0700.h>
#include "include/main.h"
#include "include/shaiya/CharacterList.h"
#include "include/shaiya/CItem.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/DBCharacterList.h"
#include "include/shaiya/ItemEnchant.h"
#include "include/shaiya/ItemInfo.h"
#include "include/shaiya/NetworkHelper.h"
using namespace shaiya;

namespace packet_character
{
    /// <summary>
    /// Handles incoming 0x119 packets.
    /// </summary>
    void handler_0x119(CUser* user, GameCharNameAvailableIncoming* incoming)
    {
        incoming->name[incoming->name.size() - 1] = '\0';
        auto nameLength = std::strlen(incoming->name.data());

        if (nameLength < 3 || nameLength > 13)
        {
            GameCharNameAvailableOutgoing outgoing{};
            outgoing.available = false;
            NetworkHelper::Send(user, &outgoing, sizeof(GameCharNameAvailableOutgoing));
            return;
        }

        DBAgentCharNameAvailableIncoming outgoing{};
        outgoing.billingId = user->billingId;
        outgoing.name = incoming->name;
        NetworkHelper::SendDBAgent(&outgoing, outgoing.baseLength + nameLength + 1);
    }

    /// <summary>
    /// Sends packet 0x119 to the user.
    /// </summary>
    void send_0x119(CUser* user, DBAgentCharNameAvailableOutgoing* incoming)
    {
        GameCharNameAvailableOutgoing outgoing{};
        outgoing.available = incoming->available;
        NetworkHelper::Send(user, &outgoing, sizeof(GameCharNameAvailableOutgoing));
    }

    /// <summary>
    /// Sends packet 0x711 (6.4) to the user. The item dates will be zero. 
    /// 
    /// EP5:   7 + 33 * 50 = 1657 // ok
    /// EP6.4: 7 + 41 * 50 = 2057 // not ok (exceeds 2048)
    /// EP6.4: 7 + 41 * 40 = 1647 // ok
    /// 
    /// </summary>
    void send_0x711(CUser* user)
    {
        GameCharBankOutgoing<BankUnit_EP6_4, 40> outgoing{};
        outgoing.bankMoney = user->bankMoney;
        outgoing.itemCount = 0;

        // Please note that warehouse access is read-only
        for (const auto& [slot, item] : std::views::enumerate(
            std::as_const(user->warehouse)))
        {
            if (!item)
                continue;

            BankUnit_EP6_4 item0711{};
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
                int length = outgoing.baseLength + (outgoing.itemCount * sizeof(BankUnit_EP6_4));
                NetworkHelper::Send(user, &outgoing, length);

                outgoing.itemCount = 0;
                outgoing.itemList = {};
            }
        }

        if (!outgoing.itemCount)
            return;

        int length = outgoing.baseLength + (outgoing.itemCount * sizeof(BankUnit_EP6_4));
        NetworkHelper::Send(user, &outgoing, length);
    }

    /// <summary>
    /// Sends packet 0x116 to the user. The client defense step values 
    /// are hard-coded to be multiples of five.
    /// </summary>
    void send_0x116(CUser* user)
    {
        GameWeaponStepOutgoing outgoing{};

        auto it = g_LapisianEnchantAddValue->step.cbegin();
        auto last = g_LapisianEnchantAddValue->step.cend();
        auto dest = outgoing.weaponStep.begin();

        for (; it != last; ++it, ++dest)
            *dest = it->weapon;

        NetworkHelper::Send(user, &outgoing, sizeof(GameWeaponStepOutgoing));
    }

    /// <summary>
    /// Sends packet 0x101 (6.4) to the user.
    /// </summary>
    void send_0x101(CUser* user, DBCharacterList_EP6_4* dbCharacter)
    {
        GameCharListOutgoing<CharacterList_EP6_4> outgoing{};
        outgoing.slot = dbCharacter->slot;
        outgoing.character.charId = dbCharacter->charId;
        outgoing.character.createDate = dbCharacter->createDate;
        outgoing.character.level = dbCharacter->level;
        outgoing.character.family = dbCharacter->family;
        outgoing.character.grow = dbCharacter->grow;
        outgoing.character.hair = dbCharacter->hair;
        outgoing.character.face = dbCharacter->face;
        outgoing.character.size = dbCharacter->size;
        outgoing.character.job = dbCharacter->job;
        outgoing.character.sex = dbCharacter->sex;
        outgoing.character.mapId = dbCharacter->mapId;
        outgoing.character.strength = dbCharacter->strength;
        outgoing.character.dexterity = dbCharacter->dexterity;
        outgoing.character.reaction = dbCharacter->reaction;
        outgoing.character.intelligence = dbCharacter->intelligence;
        outgoing.character.wisdom = dbCharacter->wisdom;
        outgoing.character.luck = dbCharacter->luck;
        outgoing.character.health = dbCharacter->health;
        outgoing.character.mana = dbCharacter->mana;
        outgoing.character.stamina = dbCharacter->stamina;
        outgoing.character.equipment = dbCharacter->equipment;
        std::memcpy(outgoing.character.charName.data(), dbCharacter->charName.data(), outgoing.character.charName.size());
        outgoing.character.enableRename = dbCharacter->enableRename;
        outgoing.character.deleted = dbCharacter->deleteDate ? true : false;
        outgoing.character.cloakInfo = dbCharacter->cloakInfo;
        NetworkHelper::Send(user, &outgoing, sizeof(GameCharListOutgoing<CharacterList_EP6_4>));
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
        call packet_character::handler_0x119
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
        call packet_character::send_0x711
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
        call packet_character::send_0x101
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
        call packet_character::send_0x119
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
        call packet_character::send_0x116
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
    util::write_memory((void*)0x47B4EC, sizeof(DBCharacterList_EP6_4), 1);
    util::write_memory((void*)0x47B9C9, sizeof(DBCharacterList_EP6_4), 1);
}
