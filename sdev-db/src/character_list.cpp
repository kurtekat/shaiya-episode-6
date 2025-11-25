#include <util/util.h>
#include <shaiya/include/network/dbAgent/outgoing/0400.h>
#include "include/main.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/DBCharacterList.h"
#include "include/shaiya/SConnection.h"
using namespace shaiya;

namespace character_list
{
    /// <summary>
    /// Sends packet 0x403 to the game service.
    /// </summary>
    void send(CUser* user, bool sendCountry)
    {
        DBAgentCharListOutgoing<DBCharacterList_EP6_4> outgoing{};
        outgoing.billingId = user->billingId;
        outgoing.withCountry = sendCountry;
        outgoing.characterCount = 0;

        for (const auto& character : user->characterList)
        {
            if (!character.charId || character.slot >= 5)
                continue;

            DBCharacterList_EP6_4 dbCharacter{};
            dbCharacter.charId = character.charId;
            dbCharacter.createDate = character.createDate;
            dbCharacter.enableRename = character.enableRename;
            dbCharacter.slot = character.slot;
            dbCharacter.family = character.family;
            dbCharacter.grow = character.grow;
            dbCharacter.hair = character.hair;
            dbCharacter.face = character.face;
            dbCharacter.size = character.size;
            dbCharacter.job = character.job;
            dbCharacter.sex = character.sex;
            dbCharacter.level = character.level;
            dbCharacter.strength = character.strength;
            dbCharacter.dexterity = character.dexterity;
            dbCharacter.reaction = character.reaction;
            dbCharacter.intelligence = character.intelligence;
            dbCharacter.wisdom = character.wisdom;
            dbCharacter.luck = character.luck;
            dbCharacter.health = character.health;
            dbCharacter.mana = character.mana;
            dbCharacter.stamina = character.stamina;
            dbCharacter.mapId = character.mapId;
            dbCharacter.deleteDate = character.deleteDate;
            dbCharacter.equipment = user->equipment[character.slot];
            dbCharacter.cloakInfo = character.cloakInfo;
            dbCharacter.charName = character.charName;

            outgoing.characterList[outgoing.characterCount] = dbCharacter;
            ++outgoing.characterCount;
        }

        if (!user->connection)
            return;

        int length = outgoing.baseLength + (outgoing.characterCount * sizeof(DBCharacterList_EP6_4));
        SConnection::Send(user->connection, &outgoing, length);
    }

    void assign_equipment(CUser* user, int characterSlot, int equipmentSlot, int type, int typeId)
    {
        if (characterSlot >= 5)
            return;

        if (equipmentSlot >= ItemListCount_EP6_4)
            return;

        user->equipment[characterSlot].type[equipmentSlot] = type;
        user->equipment[characterSlot].typeId[equipmentSlot] = typeId;
    }

    void init_equipment(CUser* user)
    {
        user->equipment = {};
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
    util::write_memory((void*)0x42220B, ItemListCount_EP6_4, 1);
}
