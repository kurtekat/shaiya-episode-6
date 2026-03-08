#include <util/util.h>
#include <shaiya/include/network/game/outgoing/0300.h>
#include "include/main.h"
#include "include/shaiya/CItem.h"
#include "include/shaiya/CloneUser.h"
#include "include/shaiya/CUser.h"
using namespace shaiya;

void hook_0x45A365(CUser* user, CUser* target)
{
    if (!user->clone)
        return;

    user->clone->dead = target->status == UserStatus::Death;
    user->clone->motion = target->motion;
    user->clone->country = target->country;
    user->clone->family = target->family;
    user->clone->hair = target->hair;
    user->clone->face = target->face;
    user->clone->size = target->size;
    user->clone->job = target->job;
    user->clone->sex = target->sex;
    user->clone->partyType = CUser::GetPartyType(target);
    user->clone->grow = target->grow;
    user->clone->kills = target->kills;

    user->clone->equipment = {};
    user->clone->charName = {};
    user->clone->cloakInfo = {};
    user->clone->guildName = {};

    for (int slot = 0; slot < 17; ++slot)
    {
        auto& item = target->inventory[0][slot];
        if (!item)
            continue;

        user->clone->equipment[slot].type = item->type;
        user->clone->equipment[slot].typeId = item->typeId;
        user->clone->equipment[slot].enchantStep = CItem::GetEnchantStep(item);
    }

    user->clone->charName = target->charName;
    user->clone->packetLength = sizeof(GameGetInfoUserShapeOutgoing_EP6_4);

    auto& cloak = target->inventory[0][7];
    if (!cloak)
    {
        user->clone->packetLength -= sizeof(CloakInfo);
        CUser::GetGuildName(target, user->clone->guildName.data());
    }
    else
    {
        user->clone->cloakInfo = cloak->gems;
        CUser::GetGuildName(target, user->clone->guildName.data());
    }
}

unsigned u0x45A246 = 0x45A246;
void __declspec(naked) naked_0x45A365()
{
    __asm
    {
        pushad

        push esi // target
        push edi // user
        call hook_0x45A365
        add esp,0x8
        
        popad

        jmp u0x45A246
    }
}

unsigned u0x411B26 = 0x411B26;
unsigned u0x51B26B = 0x51B26B;
void __declspec(naked) naked_0x411B1F()
{
    __asm
    {
        push 0x80 // size
        call u0x51B26B // malloc
        jmp u0x411B26
    }
}

void hook::user_clone()
{
    // CUser::CheckTargetUser case 2
    util::detour((void*)0x45A365, naked_0x45A365, 7);
    // CObjectMgr::CreateCloneUser
    util::detour((void*)0x411B1F, naked_0x411B1F, 7);
}
