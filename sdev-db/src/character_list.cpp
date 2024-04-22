#include <array>
#include <map>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/shaiya/include/CUser.h>
#include <sdev/include/shaiya/packets/dbAgent/0400.h>
#include <sdev/include/shaiya/include/SConnection.h>
#include <util/include/util.h>
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

        for (const auto& character : user->characterList)
        {
            if (!character.id || character.slot >= user->characterList.size())
                continue;

            Character0403 character0403{};
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

            if (auto it = g_equipment.find(user->userId); it != g_equipment.end())
                character0403.equipment = it->second[character.slot];

            character0403.cloakBadge = character.cloakBadge;
            character0403.charName = character.name;
            packet.characterList[packet.characterCount] = character0403;

            ++packet.characterCount;
        }

        if (!user->connection)
            return;

        int length = packet_size_without_list + (packet.characterCount * sizeof(Character0403));
        SConnection::Send(user->connection, &packet, length);

        g_equipment.erase(user->userId);
    }

    void insert_equipment(CUser* user)
    {
        std::array<Equipment0403, 5> equipment{};
        g_equipment.insert_or_assign(user->userId, equipment);
    }

    void assign_equipment(CUser* user, std::uint8_t characterSlot, std::uint8_t equipmentSlot, std::uint8_t type, std::uint8_t typeId)
    {
        if (characterSlot >= user->characterList.size() || equipmentSlot >= sizeof(Equipment0403) / 2)
            return;

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
        call character_list::insert_equipment
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
    util::write_memory((void*)0x42220B, sizeof(Equipment0403) / 2, 1);
}
