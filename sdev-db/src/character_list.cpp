#include <array>
#include <shaiya/include/SConnection.h>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/network/outgoing/0400.h"
using namespace shaiya;

namespace character_list
{
    /// <summary>
    /// Sends packet 0x403 to the game service.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="sendCountry">Determines whether the game service sends packet 0x109 to the user.</param>
    void send(CUser* user, bool sendCountry)
    {
        DBAgentCharListOutgoing2 outgoing{};
        outgoing.userId = user->userId;
        outgoing.sendCountry = sendCountry;
        outgoing.characterCount = 0;

        for (const auto& character : user->characterList)
        {
            if (!character.id || character.slot >= user->characterList.size())
                continue;

            Character0403v2 character0403{};
            character0403.id = character.id;
            character0403.regDate = character.regDate;
            character0403.nameChange = character.nameChange;
            character0403.slot = character.slot;
            character0403.family = character.family;
            character0403.grow = character.grow;
            character0403.hair = character.hair;
            character0403.face = character.face;
            character0403.size = character.size;
            character0403.job = character.job;
            character0403.sex = character.sex;
            character0403.level = character.level;
            character0403.strength = character.strength;
            character0403.dexterity = character.dexterity;
            character0403.reaction = character.reaction;
            character0403.intelligence = character.intelligence;
            character0403.wisdom = character.wisdom;
            character0403.luck = character.luck;
            character0403.health = character.health;
            character0403.mana = character.mana;
            character0403.stamina = character.stamina;
            character0403.mapId = character.mapId;
            character0403.deleteDate = character.deleteDate;
            std::copy_n(user->equipmentEx[character.slot].type.begin(), character0403.type.size(), character0403.type.begin());
            std::copy_n(user->equipmentEx[character.slot].typeId.begin(), character0403.typeId.size(), character0403.typeId.begin());
            character0403.cloakBadge = character.cloakBadge;
            character0403.charName = character.name;
            outgoing.characterList[outgoing.characterCount] = character0403;

            ++outgoing.characterCount;
        }

        if (!user->connection)
            return;

        int length = outgoing.size_without_list() + (outgoing.characterCount * sizeof(Character0403v2));
        SConnection::Send(user->connection, &outgoing, length);
    }

    void assign_equipment(CUser* user, uint8_t characterSlot, uint8_t equipmentSlot, uint8_t type, uint8_t typeId)
    {
        if (characterSlot >= user->characterList.size() || equipmentSlot >= max_equipment_slot)
            return;

        user->equipmentEx[characterSlot].type[equipmentSlot] = type;
        user->equipmentEx[characterSlot].typeId[equipmentSlot] = typeId;
    }

    void init_equipment(CUser* user)
    {
        user->equipmentEx = {};
    }
}

void __declspec(naked) naked_0x40AA20()
{
    __asm
    {
        pushad

        movzx edx,dl

        push edx // sendCountry
        push esi // user
        call character_list::send
        add esp,0x8

        popad

        retn
    }
}

unsigned u0x421AAB = 0x421AAB;
void __declspec(naked) naked_0x421AA5()
{
    __asm
    {
        pushad

        push edi // user
        call character_list::init_equipment
        add esp,0x4

        popad

        // original
        lea eax,[edi+0x3B98]
        jmp u0x421AAB
    }
}

unsigned u0x444CC0 = 0x444CC0;
unsigned u0x4223FE = 0x4223FE;
void __declspec(naked) naked_0x4223F7()
{
    __asm
    {
        pushad

        movzx edx,byte ptr[esp+0x42]
        push edx // typeId
        movzx eax,byte ptr[esp+0x44]
        push eax // type
        movzx edx,byte ptr[esp+0x3E]
        push edx // equipmentSlot
        movzx edx,byte ptr[esp+0x54]
        push edx // characterSlot
        push edi // user
        call character_list::assign_equipment
        add esp,0x14

        popad

        // original
        mov ecx,esi
        call u0x444CC0
        jmp u0x4223FE
    }
}

void hook::character_list()
{
    // CUser::SendCharacterList
    util::detour((void*)0x40AA20, naked_0x40AA20, 6);
    // DBCharacter::LoadCharacterList
    util::detour((void*)0x421AA5, naked_0x421AA5, 6);
    util::detour((void*)0x4223F7, naked_0x4223F7, 7);
    // DBCharacter::LoadCharacterList
    util::write_memory((void*)0x42220B, max_equipment_slot, 1);
}
