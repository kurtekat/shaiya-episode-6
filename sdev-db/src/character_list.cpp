#include <util/util.h>
#include <shaiya/include/network/dbAgent/outgoing/0400.h>
#include "include/main.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/DBCharacterList.h"
#include "include/shaiya/SConnection.h"
using namespace shaiya;

/// <summary>
/// Sends packet 0x403 to the game service.
/// </summary>
void hook_0x40AA20(CUser* user, bool sendCountry)
{
    DBAgentCharListOutgoing<DBCharacterList_EP6_4> outgoing{};
    outgoing.billingId = user->billingId;
    // The game service sends packet 0x109 to the client 
    // if this value is true
    outgoing.withCountry = sendCountry;
    outgoing.characterCount = 0;
    // The game service copies most of this data to a 0x101 packet 
    // and then sends the packet to the client
    auto character = outgoing.characterList.begin();
    auto equipment = user->equipment.cbegin();

    for (const auto& e : user->characterList)
    {
        if (!e.charId)
            continue;

        character->charId = e.charId;
        character->createDate = e.createDate;
        character->enableRename = e.enableRename;
        character->slot = e.slot;
        character->family = e.family;
        character->grow = e.grow;
        character->hair = e.hair;
        character->face = e.face;
        character->size = e.size;
        character->job = e.job;
        character->sex = e.sex;
        character->level = e.level;
        character->strength = e.strength;
        character->dexterity = e.dexterity;
        character->reaction = e.reaction;
        character->intelligence = e.intelligence;
        character->wisdom = e.wisdom;
        character->luck = e.luck;
        character->health = e.health;
        character->mana = e.mana;
        character->stamina = e.stamina;
        character->mapId = e.mapId;
        character->deleteDate = e.deleteDate;
        character->equipment = *(equipment + e.slot);
        character->cloakInfo = e.cloakInfo;
        character->charName = e.charName;

        ++character;
        ++outgoing.characterCount;
    }

    if (!user->connection)
        return;

    int length = outgoing.baseLength + (outgoing.characterCount * sizeof(DBCharacterList_EP6_4));
    SConnection::Send(user->connection, &outgoing, length);
}

void hook_0x421AA5(CUser* user)
{
    user->equipment = {};
}

// The dbAgent service checks the character slot at 0x421F04
void hook_0x4223F7(CUser* user, int characterSlot, int equipmentSlot, int type, int typeId)
{
    if (equipmentSlot >= 17)
        return;

    user->equipment[characterSlot].type[equipmentSlot] = type;
    user->equipment[characterSlot].typeId[equipmentSlot] = typeId;
}

void __declspec(naked) naked_0x40AA20()
{
    __asm
    {
        pushad

        movzx edx,dl

        push edx // sendCountry
        push esi // user
        call hook_0x40AA20
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
        call hook_0x421AA5
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
        call hook_0x4223F7
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
    util::write_memory((void*)0x42220B, 17, 1);
}
