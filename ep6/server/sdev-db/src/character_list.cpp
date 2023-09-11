#include <array>
#include <map>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>

#include <shaiya/packets/0403.h>
#include <shaiya/include/CUser.h>
#include <shaiya/include/SConnection.h>
using namespace shaiya;

namespace character_list
{
    constexpr int max_character_slot = 5;
    constexpr int max_equipment_slot = 17;

    inline std::map<UserId, std::array<Equipment0403, 5>> equipment_map{};

    void send(CUser* user, bool sendCountry)
    {
        CharacterList character_list{};
        character_list.opcode = 0x403;
        character_list.userId = user->userId;
        character_list.sendCountry = sendCountry;
        character_list.count = 0;

        for (int i = 0; i < max_character_slot; ++i)
        {
            if (!user->character[i].id)
                continue;

            Character0403 character{};
            character.id = user->character[i].id;
            character.regDate = user->character[i].regDate;
            character.deleted = user->character[i].deleted;
            character.slot = user->character[i].slot;
            character.family = user->character[i].family;
            character.grow = user->character[i].grow;
            character.hair = user->character[i].hair;
            character.face = user->character[i].face;
            character.size = user->character[i].size;
            character.job = user->character[i].job;
            character.sex = user->character[i].sex;
            character.level = user->character[i].level;
            character.strength = user->character[i].strength;
            character.dexterity = user->character[i].dexterity;
            character.reaction = user->character[i].reaction;
            character.intelligence = user->character[i].intelligence;
            character.wisdom = user->character[i].wisdom;
            character.luck = user->character[i].luck;
            character.health = user->character[i].health;
            character.mana = user->character[i].mana;
            character.stamina = user->character[i].stamina;
            character.mapId = user->character[i].mapId;
            character.nameChange = user->character[i].nameChange;

            auto it = equipment_map.find(user->userId);
            if (it != equipment_map.end())
                std::memcpy(&character.equipment, &it->second[i], sizeof(Equipment0403));
            else
                // better than nothing :P
                std::memcpy(&character.equipment, &user->character[i].equipment, sizeof(Equipment));

            std::memcpy(&character.cloakBadge, &user->character[i].cloakBadge, sizeof(CloakBadge));
            strncpy_s(character.charName, user->character[i].charName, sizeof(character.charName));

            std::memcpy(&character_list.list[i], &character, sizeof(Character0403));
            ++character_list.count;
        }

        if (!user->connection)
            return;

        constexpr int packet_size_without_list = 8;
        int packet_size = packet_size_without_list + (character_list.count * sizeof(Character0403));
        SConnection::Send(user->connection, &character_list, packet_size);
    }

    void make_equipment_pair(CUser* user)
    {
        auto it = equipment_map.find(user->userId);
        if (it == equipment_map.end())
        {
            std::array<Equipment0403, 5> equipment{};
            auto pair = std::make_pair(user->userId, equipment);
            equipment_map.insert(pair);
        }
    }

    void init_equipment(CUser* user, int characterSlot, int equipmentSlot, int type, int typeId)
    {
        auto it = equipment_map.find(user->userId);
        if (it != equipment_map.end())
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
        call character_list::make_equipment_pair
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

    std::uint8_t read_items_slot_param = 17;
    util::write_memory((void*)0x42220B, &read_items_slot_param, 1);
}
