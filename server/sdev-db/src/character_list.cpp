#include <array>
#include <map>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>
#include <include/shaiya/include/CUser.h>
#include <sdev/include/shaiya/packets/dbAgent/0400.h>
#include <sdev/include/shaiya/include/SConnection.h>
using namespace shaiya;

namespace character_list
{
    inline std::map<UserId, std::array<Equipment0403, 5>> g_equipment{};

    void send(CUser* user, bool sendCountry)
    {
        constexpr int packet_size_without_list = 8;

        UserCharListOutgoing packet{};
        packet.userId = user->userId;
        packet.sendCountry = sendCountry;
        packet.characterCount = 0;

        for (int slot = 0; slot < max_character_slot; ++slot)
        {
            if (!user->characterList[slot].id)
                continue;

            Character0403 character{};
            character.id = user->characterList[slot].id;
            character.regDate = user->characterList[slot].regDate;
            character.deleted = user->characterList[slot].deleted;
            character.slot = user->characterList[slot].slot;
            character.family = user->characterList[slot].family;
            character.grow = user->characterList[slot].grow;
            character.hair = user->characterList[slot].hair;
            character.face = user->characterList[slot].face;
            character.size = user->characterList[slot].size;
            character.job = user->characterList[slot].job;
            character.sex = user->characterList[slot].sex;
            character.level = user->characterList[slot].level;
            character.strength = user->characterList[slot].strength;
            character.dexterity = user->characterList[slot].dexterity;
            character.reaction = user->characterList[slot].reaction;
            character.intelligence = user->characterList[slot].intelligence;
            character.wisdom = user->characterList[slot].wisdom;
            character.luck = user->characterList[slot].luck;
            character.health = user->characterList[slot].health;
            character.mana = user->characterList[slot].mana;
            character.stamina = user->characterList[slot].stamina;
            character.mapId = user->characterList[slot].mapId;
            character.nameChange = user->characterList[slot].nameChange;

            if (auto it = g_equipment.find(user->userId); it != g_equipment.end())
                character.equipment = it->second[slot];

            character.cloakBadge = user->characterList[slot].cloakBadge;
            character.charName = user->characterList[slot].name;
            packet.characterList[slot] = character;

            ++packet.characterCount;
        }

        if (!user->connection)
            return;

        int length = packet_size_without_list + (packet.characterCount * sizeof(Character0403));
        SConnection::Send(user->connection, &packet, length);

        g_equipment.erase(user->userId);
    }

    void make_equipment(CUser* user)
    {
        std::array<Equipment0403, 5> equipment{};
        g_equipment.insert_or_assign(user->userId, equipment);
    }

    void init_equipment(CUser* user, int characterSlot, int equipmentSlot, int type, int typeId)
    {
        if (auto it = g_equipment.find(user->userId); it != g_equipment.end())
        {
            it->second[characterSlot].type[equipmentSlot] = type;
            it->second[characterSlot].typeId[equipmentSlot] = typeId;
        }
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
        call character_list::make_equipment
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
        call character_list::init_equipment
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
    util::write_memory((void*)0x42220B, item_list_size, 1);
}
